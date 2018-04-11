#include <irrlicht.h>
#include "driverChoice.h"
#include <vector>
#include <mutex>
#include "CardStack.h"
#include "EventReceiver.h"
#include "CommonVars.h"
#include "CardSceneNode.h"

using namespace irr;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.a")
#endif

CommonVars Vars;

void distribute(CardStack *Reserve, CardStack *Player, CardStack *CPU)
{
    int PlayersTurnToDistribute = 1; // 1 : humans turn to play, 0 : ai

	// Distribute 27 cards to players starting with human
	for (int i = 0; i < 27; i++)
	{
		if ( (i+PlayersTurnToDistribute) & 1) Vars.ReserveStack->TransferCardTo(Vars.PlayerStack);
		else Vars.ReserveStack->TransferCardTo(Vars.CpuStack);
	}
}

void setSkinTransparency(s32 alpha, irr::gui::IGUISkin * skin)
{
    for (s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
        video::SColor col = skin->getColor((gui::EGUI_DEFAULT_COLOR)i);
        col.setAlpha(alpha);
        skin->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
    }
}

int main()
{
	// Irrlicht init
	video::E_DRIVER_TYPE driverType = video::E_DRIVER_TYPE::EDT_OPENGL;
	MyEventReceiver receiver(&Vars);
	Vars.device = createDevice(driverType, core::dimension2d<u32>(1280, 800), 16, false, false, false, &receiver);
	if (Vars.device == 0) return 1; // could not create selected driver.
    
    // -------- create gui ----------
    Vars.env = Vars.device->getGUIEnvironment();
    Vars.device->setResizable(true);
    gui::IGUISkin* skin = Vars.env->getSkin();
    /*gui::IGUIFont* font = Vars.env->getFont("./Media/BigFont.png");
    if (font)
        skin->setFont(font);
    skin->setFont(Vars.env->getBuiltInFont(), gui::EGDF_TOOLTIP);*/
    //setSkinTransparency(255, Vars.env->getSkin());
    gui::IGUIWindow* window = Vars.env->addWindow(
                        core::rect<s32>(10 , 10 , 300 , 200 ),
                        false, // modal?
                        L"Test window");
                        
                         
    
    Vars.env->addButton(core::rect<s32>(10,240,110,240 + 32), 0, GUI_ID_QUIT_BUTTON, L"Quit", L"");
    Vars.env->addButton(core::rect<s32>(10,280,110,280 + 32), 0, GUI_ID_PUTDOWN_BUTTON, L"Put down", L"");
    
	Vars.device->setWindowCaption(L"Loading...");
	Vars.driver = Vars.device->getVideoDriver();
	Vars.smgr = Vars.device->getSceneManager();
	Vars.cam = Vars.smgr->addCameraSceneNode(0, core::vector3df(0,-40,0), core::vector3df(0,0,0));
	Vars.cam->setNearValue(50.0f);
	Vars.cam->setFarValue(250.0f);
    

    Vars.ReserveStack = new CardStack(&Vars);
    Vars.PlayerStack  = new CardStack(&Vars);
    Vars.CpuStack     = new CardStack(&Vars);

	// Whole Game init
	Vars.ReserveStack->fillup_card_game();
	Vars.ReserveStack->RandomizeOrder();
	Vars.ReserveStack->SetPosition(irr::core::vector2df(0, -35));

	// Player's Game init
	Vars.PlayerStack->SetPosition(irr::core::vector2df(-22, -10));

	// Computer's Game init
	Vars.CpuStack->SetPosition(irr::core::vector2df(22, -10));

	distribute(Vars.ReserveStack, Vars.PlayerStack, Vars.CpuStack);

	Vars.ReserveStack->refreshPos(false);
	Vars.PlayerStack->refreshPos(true);
	Vars.CpuStack->refreshPos(true);
    
    Vars.CurrentGameState = Player_Draw;
/*
 * --------------------------- Frame Loop -------------------------
*/
	u32 frames=0;
	while(Vars.device->run())
	{
		Vars.driver->beginScene(true, true, video::SColor(0,3,30,3));
		Vars.smgr->drawAll();
        Vars.env->drawAll();
		Vars.driver->endScene();
		if (++frames==100)
		{
			core::stringw str = L"Rami by SkyZoThreaD [";
			str += Vars.driver->getName();
			str += L"] FPS: ";
			str += (s32)Vars.driver->getFPS();

			Vars.device->setWindowCaption(str.c_str());
			frames=0;
		}
	}

	Vars.device->drop();
	
	return 0;
}
