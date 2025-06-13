#pragma once
#include "Card.h"
#include "HeterogeneousContainer.hpp"

class CardDeck
{
	CardDeck();
	static CardDeck* instance;
	HeterogeneousContainer<Card> chanceCards;
	HeterogeneousContainer<Card> communityChestCards;

public:
	void InitializeCardDeck();
	static CardDeck* getInstance();
	static void destroyInstance();
};

