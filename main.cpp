#include <irrlicht.h>
#include "driverChoice.h"
#include <vector>
#include "PlayerStock.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#include "CardSceneNode.h"

scene::ISceneManager* smgr;
video::IVideoDriver* driver;
scene::ICameraSceneNode *cam;



scene::ISceneNode* ScreenPick (s32 x,s32 y,scene::ITriangleSelector* selector)
{
		core::line3d<f32> ray;
        ray.start = cam->getPosition();
        ray.end = ray.start + (cam->getTarget() - ray.start).normalize() * 1000.0f;

        // Tracks the current intersection point with the level or a mesh
        core::vector3df intersection;
        // Used to show with triangle has been hit
        core::triangle3df hitTriangle;

        // This call is all you need to perform ray/triangle collision on every scene node
        // that has a triangle selector, including the Quake level mesh.  It finds the nearest
        // collision point/triangle, and returns the scene node containing that point.
        // Irrlicht provides other types of selection, including ray/triangle selector,
        // ray/box and ellipse/triangle selector, plus associated helpers.
        // See the methods of ISceneCollisionManager
		
		scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();
        scene::ISceneNode * selectedSceneNode =
            collMan->getSceneNodeAndCollisionPointFromRay(
                    ray,
                    intersection, // This will be the position of the collision
                    hitTriangle, // This will be the triangle hit in the collision
                    0, // This ensures that only nodes that we have
                            // set up to be pickable are considered
                    0); // Check the entire scene (this is actually the implicit default)
					
	return selectedSceneNode;
}



class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			std::cout << "BLA.."<<std::endl;
			
			scene::ITriangleSelector* selector = 0;
			//scene::ISceneNode *n = ScreenPick (event.MouseInput.X, event.MouseInput.Y, selector);
			
			scene::ISceneNode *n = smgr->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y));
			
			if(n) n->setPosition( n->getPosition()+core::vector3df(1.0,0.0,0.0) );
		}
		else if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
			event.KeyInput.Key == KEY_KEY_S && event.KeyInput.PressedDown)
		{
			return true;
		}
		return true;
	}
};

void fillup_card_game( PlayerStock *stock )
{
	CSampleSceneNode *myNode;
	
	for( int i=0; i<2; i++)
	{
		myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666, driver, CardType(CardColor::Jocker, 0));
		stock->AddCard(new Card(CardType(CardColor::Jocker, 0), myNode));
	}
	
	for( int color = 0; color < 4; color++ )
		for ( int nb = 0; nb < 13; nb++ )
		{
			myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666, driver, CardType((CardColor)color, nb));
			stock->AddCard(new Card(CardType((CardColor)color, nb), myNode));
		}
}

int main()
{
	// Irrlicht init
	video::E_DRIVER_TYPE driverType = video::E_DRIVER_TYPE::EDT_OPENGL;
	MyEventReceiver receiver;
	IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(1280, 800), 16, false, false, false, &receiver);
	if (device == 0) return 1; // could not create selected driver.
	device->setWindowCaption(L"Loading...");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	cam = smgr->addCameraSceneNode(0, core::vector3df(0,-40,0), core::vector3df(0,0,0));
	cam->setNearValue(50.0f);
	cam->setFarValue(250.0f);

	// Whole Game init
	PlayerStock CardGame;
	fillup_card_game(&CardGame);
	CardGame.RandomizeOrder();
	CardGame.SetPosition(irr::core::vector2df(0, -35));

	// Player's Game init
	PlayerStock PlayerGame;
	PlayerGame.SetPosition(irr::core::vector2df(-22, -10));

	// Computer's Game init
	PlayerStock AIGame;
	AIGame.SetPosition(irr::core::vector2df(22, -10));

	int PlayersTurnToDistribute = 1; // 1 : humans turn to play, 0 : ai

	// Distribute 27 cards to players starting with human
	for (int i = 0; i < 27; i++)
	{
		if ( (i+PlayersTurnToDistribute) & 1) CardGame.TransferCardTo(PlayerGame);
		else CardGame.TransferCardTo(AIGame);
	}

	CardGame.refreshPos(false);
	PlayerGame.refreshPos(true);
	AIGame.refreshPos(true);	

	/*
	Now draw everything and finish.
	*/
	u32 frames=0;
	while(device->run())
	{
		driver->beginScene(true, true, video::SColor(0,3,30,3));

		smgr->drawAll();

		driver->endScene();
		if (++frames==100)
		{
			core::stringw str = L"Rami by SkyZoThreaD [";
			str += driver->getName();
			str += L"] FPS: ";
			str += (s32)driver->getFPS();

			device->setWindowCaption(str.c_str());
			frames=0;
		}
	}

	device->drop();
	
	return 0;
}
