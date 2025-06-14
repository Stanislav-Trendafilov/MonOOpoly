#pragma once
#include "Field.h"
#include "Player.h"
#include "CardDeck.h"

class CardField	:public Field
{
	CardDeck* deck;
public:
	CardField(const MyString& name, size_t boardIndex);

	void DrawChanceCard(Player& player);

	void DrawCommunityCard(Player& player);

	void ApplyAction(Player& player);

	Field* clone() const override;
};

