#pragma once
#include "Field.h"
#include "Player.h"
#include "CardDeck.h"
#include "MyString.h"

class CardField	:public Field
{
	CardDeck* deck;
	MyString typeOfCard;
public:
	CardField(const MyString& name, size_t boardIndex,const MyString& typeOfCard);

	void ApplyAction(Player& player) override;

	Field* clone() const override;
};

