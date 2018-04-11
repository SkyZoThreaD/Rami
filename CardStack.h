#pragma once

#include <irrlicht.h>
#include "Card.h"
#include "CardSceneNode.h"
#include "CommonVars.h"
#include <ctime>
#include <vector>

class CardStack
{
	std::vector<Card*> Cards;
	irr::core::vector2df ScreenPosition;
    CommonVars *vars;

public:
	CardStack(CommonVars *_vars);
	void AddCard(Card *n);
	void empty();
	void treatActivation(irr::scene::ISceneNode *n);
    bool IsAPartOf(irr::scene::ISceneNode *n);
	void SetPosition(irr::core::vector2df p);
	void TransferCardTo(CardStack *other);
	void refreshPos(bool deployed);
	void RandomizeOrder();
    void fillup_card_game();
};