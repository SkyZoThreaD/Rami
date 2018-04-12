#pragma once

#include "CardStack.h"
#include <vector>

class CardStack;

enum GameState{
    Player_Draw   = 0,
    Player_Put    = 1,
    Computer_Draw = 2,
    Computer_Put  = 3
};

struct CommonVars
{
    scene::ISceneManager* smgr;
    video::IVideoDriver* driver;
    irr::IrrlichtDevice* device;
    scene::ICameraSceneNode *cam;
    irr::gui::IGUIEnvironment* env;
    CardStack *ReserveStack;
    CardStack *TrashStack;
    CardStack *PlayerStack;
    CardStack *CpuStack;
    GameState CurrentGameState;
	irr::gui::IGUIButton *PutDownBut;
    std::vector<CardStack*> StacksOnTable;
};