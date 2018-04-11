#pragma once

#include <irrlicht.h>

//globals
static irr::f32 Card_TC_U = 1.0 / 13.0;
static irr::f32 Card_TC_V = 1.0 / 4.0;

enum CardColor {
	Hearts,
	Tile,
	Clover,
	Pike,
	Jocker
};

struct TC_area
{
	irr::f32 u_min;
	irr::f32 u_max;
	irr::f32 v_min;
	irr::f32 v_max;
};

class CardType{
public:
	CardColor	m_col;
	int			m_val;

	CardType(CardColor col, int val);
};

struct TC_area TC_from_CardType(CardType type);