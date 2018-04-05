#pragma once

#include "CardType.h"
#include <irrlicht.h>

// globals
static irr::f32 CardOffset_Depth = -0.1;
static irr::f32 CardOffset_Side = 1.9;

class Card
{
public:
	CardType m_type;
	irr::scene::ISceneNode *Node;
	int Val;

	Card(CardType t, irr::scene::ISceneNode *n):
		m_type(t),
		Node(n){}
};