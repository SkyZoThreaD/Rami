/** Example 003 Custom SceneNode

This Tutorial is more advanced than the previous ones.
If you are currently just playing around with the Irrlicht
engine, you may want to look at other examples first.
This tutorials shows how to create a custom scene node and
how to use it in the engine. A custom scene node is needed
if you want to implement a render technique the Irrlicht
Engine currently does not support. For example, you can write
an indoor portal based renderer or an advanced terrain scene
node with it. By creating custom scene nodes, you can
easily extend the Irrlicht Engine and adapt it to your own
needs.

I will keep the tutorial simple: Keep everything very
short, everything in one .cpp file, and I'll use the engine
here as in all other tutorials.

To start, I include the header files, use the irr namespace,
and tell the linker to link with the .lib file.
*/
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

class MyEventReceiver : public IEventReceiver
{
public:
	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			
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
	stock->empty();
	for( int color = 0; color < 4; color++ )
		for ( int nb = 0; nb < 13; nb++ )
		{
			CSampleSceneNode *myNode = new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666, driver, CardType((CardColor)color, nb));
			stock->AddCard(new Card(CardType((CardColor)color, nb), myNode));
		}
}

int main()
{
	// Irrlicht init
	video::E_DRIVER_TYPE driverType = video::E_DRIVER_TYPE::EDT_OPENGL; //driverChoiceConsole();
	MyEventReceiver receiver;
	IrrlichtDevice *device = createDevice(driverType, core::dimension2d<u32>(1280, 800), 16, false, false, false, &receiver);
	if (device == 0) return 1; // could not create selected driver.
	device->setWindowCaption(L"Loading...");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	smgr->addCameraSceneNode(0, core::vector3df(0,-40,0), core::vector3df(0,0,0));

	// Whole Game init
	PlayerStock CardGame;
	fillup_card_game(&CardGame);
	CardGame.RandomizeOrder();
	CardGame.SetPosition(irr::core::vector2df(0, -20));

	// Player's Game init
	PlayerStock PlayerGame;
	PlayerGame.SetPosition(irr::core::vector2df(-22, -20));

	// Computer's Game init
	PlayerStock AIGame;
	PlayerGame.SetPosition(irr::core::vector2df(-22, 10));

	int PlayersTurnToDistribute = 1; // 1 : humans turn to play, 0 : ai

	// Distribute 27 cards to players starting with human
	for (int i = 0; i < 27; i++)
	{
		if ( (i+PlayersTurnToDistribute) & 1) CardGame.TransferCardTo(PlayerGame);
		else CardGame.TransferCardTo(AIGame);
	}

	CardGame.refreshPos(false);
	PlayerGame.refreshPos(true);
	PlayerGame.refreshPos(true);

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
