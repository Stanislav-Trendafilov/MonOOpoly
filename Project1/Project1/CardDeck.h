#pragma once
#include "Card.h"
#include "HeterogeneousContainer.hpp"
#include "MyVector.hpp"
#include <random>


class CardDeck
{
	CardDeck();
	static CardDeck* instance;
	HeterogeneousContainer<Card> chanceCards;
	HeterogeneousContainer<Card> communityChestCards;

	MyVector<int> chanceOrder;
	MyVector<int> communityOrder;
	size_t chanceIndex;
	size_t communityIndex;

public:
	void InitializeCardDeck();
	static CardDeck* getInstance();
	static void destroyInstance();

	void ShuffleDecks();
	Card* DrawChanceCard();
	Card* DrawCommunityChestCard();
};

