#pragma once

#include <irrlicht.h>
#include "Card.h"
#include <ctime>

class PlayerStock
{
	std::vector<Card*> Cards;
	irr::core::vector2df ScreenPosition;

public:
	PlayerStock()
	{
		Cards.empty();
	}

	void AddCard(Card *n)
	{
		Cards.push_back(n);
	}

	void empty()
	{
		Cards.empty();
	}

	void treatActivation(irr::scene::ISceneNode *n)
	{
		for(auto c : Cards)
		{
			if(n == c->Node)
			{
				if(!c->activated)
				{
					c->activated = true;
					c->Node->setPosition(c->Node->getPosition()+ irr::core::vector3df(3,0,0));
				}
				else
				{
					c->activated = false;
					c->Node->setPosition(c->Node->getPosition()+ irr::core::vector3df(-3,0,0));
				}
			}
		}
	}

	void SetPosition(irr::core::vector2df p)
	{
		ScreenPosition = p;
	}

	void TransferCardTo(PlayerStock &other)
	{
		other.Cards.push_back(Cards.back());
		Cards.pop_back();
	}

	void refreshPos(bool deployed)
	{
		irr::f32 i = 0;
		for (auto v : Cards)
		{
			if(deployed) v->Node->setPosition(irr::core::vector3df(ScreenPosition.X, 0, ScreenPosition.Y) + irr::core::vector3df(0, i*CardOffset_Depth, i*CardOffset_Side));
			else v->Node->setPosition(irr::core::vector3df(ScreenPosition.X, 0, ScreenPosition.Y)+ irr::core::vector3df(0, i*CardOffset_Depth, 0));
			i += 1.0;
		}
	}

	void RandomizeOrder()
	{
		std::vector<Card*> Buffer;

		// generate random results
		srand(time(NULL));
		for(auto v : Cards) v->Val = rand() % 100000;

		while (Cards.size() > 0)
		{
			std::vector<Card*>::iterator Highest = Cards.begin();
			for (std::vector<Card*>::iterator v = Cards.begin(); v != Cards.end(); ++v)
				if ((*v)->Val > (*Highest)->Val) {
					Highest = v;
				}

			Buffer.push_back( (*Highest) );
			Cards.erase(Highest);
		}
		
		Cards = Buffer;
	}
};