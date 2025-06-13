#pragma once
#include "Card.h"

class MovePositionCard :public Card
{
	int moveWith;
public:
	MovePositionCard(const MyString& name, const MyString& effect, int moveWith);

	void applyEffect(Player& player) override;

	Card* clone() const override;

};

