#include "CardType.h"

struct TC_area TC_from_CardType(CardType type)
{
	TC_area ret;
	switch (type.m_col)
	{
	case Clover:	ret.v_min = Card_TC_V * 0; break;
	case Tile:	ret.v_min = Card_TC_V * 1; break;
	case Hearts: ret.v_min = Card_TC_V * 2; break;
	case Pike:	ret.v_min = Card_TC_V * 3; break;
	case Joker:
		ret.v_min = ret.u_min = 0;
		ret.v_max = ret.u_max = 1;
		return ret;
		break;
	default: break;
	}

	ret.v_max = ret.v_min + Card_TC_V;
	ret.u_min = Card_TC_U * type.m_val;
	ret.u_max = ret.u_min + Card_TC_U;
	return ret;
}

CardType::CardType(CardColor col, int val):
		m_col(col),
		m_val(val)
{}