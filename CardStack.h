#pragma once

#include <irrlicht.h>
#include "Card.h"
#include "CardSceneNode.h"
#include "CommonVars.h"
#include <ctime>
#include <vector>

struct ComboType
{
    std::vector<Card*> Cards;
};

class CardStack
{
	irr::core::vector2df ScreenPosition;
    CommonVars *vars;
public:
    std::vector<Card*> Cards;


	CardStack(CommonVars *_vars);
	void AddCard(Card *n);
	void empty();
	void treatActivation(irr::scene::ISceneNode *n);
	int  howManyActivated();
	bool putCombo();
    Card *getFirstJoker();
    bool IsAPartOf(irr::scene::ISceneNode *n);
	void SetPosition(irr::core::vector2df p);
	void TransferCardTo(CardStack *other, Card *card = nullptr);
	void refreshPos(bool deployed);
	void RandomizeOrder();
    void fillup_card_game();
};