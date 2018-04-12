#include "CardStack.h"

CardStack::CardStack(CommonVars *_vars):vars(_vars)
{
    Cards.empty();
}

bool CardStack::putCombo()
{
	bool sameColor = true;
	int JokerNb = 0;
	
	std::vector<Card*> Combo;
	// get selected cards
	for(auto c : Cards)
		if(c->activated) 
			if(c->m_type.m_col != Joker) Combo.push_back(c); // trick : remove jokes from selection
			else JokerNb ++;                                 // so i can do what follows...
	
	// check they are all the same color
	CardColor col = ( *(Combo.back()) ).m_type.m_col; // pick the color of one
	for(auto c : Combo) if (c->m_type.m_col != col) sameColor = false; // compare to all other
	if(sameColor)
	{
		// might be a Run...
        Card *lowest, *last = nullptr;
        int consecutive = 0;
		while(Combo.size() > 0)
        {
            lowest = nullptr;
            for( auto c : Combo ) // identify lowest card
            {
                if(lowest == nullptr) // first
                    lowest = c;
                else if(c->m_type.m_val < lowest->m_type.m_val)
                    lowest = c;
            }
            if(last != nullptr) // not first
            {
                // check how many Jockers we need
                int jokneed = lowest->m_type.m_val - last->m_type.m_val;
                if(jokneed <= JokerNb)
                {
                    JokerNb -= jokneed;
                    for(int i=0; i<jokneed; i++) // put joks
                    {
                        Card *j = getFirstJoker();
                        if(j!=nullptr) ret.Cards.push_back( j );
                    }
                    ret.Cards.push_back( lowest );
                    consecutive += jokneed + 1;
                }
                else
                {
                    if(consecutive >= 3) // run is long enough
                        return true; 
                    else
                        
                        return false; 
                }
            }
            else
            {
                ret.Cards.push_back( lowest ); // first lap
                
            }
            
            last = lowest;
        }
	}
	else
	{
		// might be a trip or more
        
	}
    return false;
}

Card *CardStack::getFirstJoker()
{
    for( auto c : Cards )
        if(c->m_type.m_col == Joker) return c;
    return nullptr;
}

int CardStack::howManyActivated()
{
	int ret = 0;
	for( auto c : Cards)
		if(c->activated) ret++;
	return ret;
}

void CardStack::AddCard(Card *n)
{
    Cards.push_back(n);
}

void CardStack::empty()
{
    Cards.empty();
}

bool CardStack::IsAPartOf(irr::scene::ISceneNode *n)
{
    for(auto c : Cards) if(n == c->Node) return true;
    return false;
}

void CardStack::treatActivation(irr::scene::ISceneNode *n)
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

void CardStack::SetPosition(irr::core::vector2df p)
{
    ScreenPosition = p;
}

void CardStack::TransferCardTo(CardStack *other, Card *card)
{
    if(card != nullptr)
    {
        for( std::vector<Card*>::iterator it = Cards.begin(); it != Cards.end(); ++it )
            if( (*it)->Node == card->Node) // found card
            {
                other->Cards.push_back(*it);
                Cards.erase(it);
            }
    }
    other->Cards.push_back(Cards.back());
    Cards.pop_back();
}

void CardStack::refreshPos(bool deployed)
{
    irr::f32 i = 0;
    for (auto v : Cards)
    {
        if(deployed) v->Node->setPosition(irr::core::vector3df(ScreenPosition.X, 0, ScreenPosition.Y) + irr::core::vector3df(0, i*CardOffset_Depth, i*CardOffset_Side));
        else v->Node->setPosition(irr::core::vector3df(ScreenPosition.X, 0, ScreenPosition.Y)+ irr::core::vector3df(0, i*CardOffset_Depth, 0));
        i += 1.0;
    }
}

void CardStack::RandomizeOrder()
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
    
void CardStack::fillup_card_game()
{
    CardSceneNode *myNode;
        
    for( int i=0; i<2; i++)
    {
        myNode = new CardSceneNode(vars->smgr->getRootSceneNode(), vars->smgr, 666, vars->driver, CardType(Joker, 0));
        AddCard(new Card(CardType(Joker, 0), myNode));
    }
        
    for( int color = 0; color < 4; color++ )
        for ( int nb = 0; nb < 13; nb++ )
        {
            myNode = new CardSceneNode(vars->smgr->getRootSceneNode(), vars->smgr, 666, vars->driver, CardType((CardColor)color, nb));
            AddCard(new Card(CardType((CardColor)color, nb), myNode));
        }
}