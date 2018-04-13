#pragma once

#include <irrlicht.h>
#include "CardStack.h"
#include "CommonVars.h"

enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_PUTDOWN_BUTTON
};


class MyEventReceiver : public IEventReceiver
{
    CommonVars *vars;
    
public:
    MyEventReceiver(CommonVars *_vars):vars(_vars)
    {
    }

	virtual bool OnEvent(const SEvent& event)
	{
        // ----------------------- GUI EVENTS -------------
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            switch(event.GUIEvent.EventType)
            {
                case gui::EGET_BUTTON_CLICKED:
                switch(id)
                {
                case GUI_ID_QUIT_BUTTON:
                    vars->device->closeDevice();
                    return false;
				case GUI_ID_PUTDOWN_BUTTON:
					if(vars->CurrentGameState == Player_Put) // useful ?
					{
                        vars->PlayerStack->putCombo();
					}
					return false;
                }
            }
        }
        
        // ----------------------- Mouse EVENTS -------------
		else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			if(event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)//event.MouseInput.isLeftPressed())
			{
                scene::ISceneNode *n;
                switch(vars->CurrentGameState)
                {
                    case GameState::Player_Draw:
                        n = vars->smgr->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y));
                        if(n)
                            if(vars->ReserveStack->IsAPartOf(n)) // We clicked on the reserve stack
                            {
                                vars->ReserveStack->TransferCardTo(vars->PlayerStack); // pick the first card
                                vars->PlayerStack->refreshPos(true);
                                vars->CurrentGameState = Player_Put; // switch state
                            }
                            break;
                    case GameState::Player_Put:
                        n = vars->smgr->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(core::position2d<s32>(event.MouseInput.X, event.MouseInput.Y));
                        if(n) vars->PlayerStack->treatActivation(n);
						if(vars->PlayerStack->howManyActivated() > 0) vars->PutDownBut->setVisible(true);
						else vars->PutDownBut->setVisible(false);
                        break;
                    case GameState::Computer_Draw:
                    case GameState::Computer_Put:
                        break;
                }
				return false;
			}
		}
		else if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
			event.KeyInput.Key == KEY_KEY_S && event.KeyInput.PressedDown)
		{
			return false;
		}
		return false;
	}
};