#pragma once

#include <irrlicht.h>

//globals
static irr::f32 Card_TC_U = 1.0 / 13.0;
static irr::f32 Card_TC_V = 1.0 / 4.0;

enum CardColor {
	Hearts,
	Tile,
	Clover,
	Pike
};

class CardType{

public:
	CardColor	m_col;
	int			m_val;

	CardType(CardColor col, int val):
		m_col(col),
		m_val(val)
	{}
};

struct TC_area
{
	irr::f32 u_min;
	irr::f32 u_max;
	irr::f32 v_min;
	irr::f32 v_max;
};

TC_area TC_from_CardType(CardType type)
{
	TC_area ret;
	switch (type.m_col)
	{
	case CardColor::Clover:	ret.v_min = Card_TC_V * 0; break;
	case CardColor::Tile:	ret.v_min = Card_TC_V * 1; break;
	case CardColor::Hearts: ret.v_min = Card_TC_V * 2; break;
	case CardColor::Pike:	ret.v_min = Card_TC_V * 3; break;
	default: break;
	}

	ret.v_max = ret.v_min + Card_TC_V;
	ret.u_min = Card_TC_U * type.m_val;
	ret.u_max = ret.u_min + Card_TC_U;
	return ret;
}