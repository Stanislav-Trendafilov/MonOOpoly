#pragma once
#include "Card.h"

class MovePositionCard :public Card
{
	size_t moveWith;
public:
	MovePositionCard(const MyString& name, const MyString& effect, size_t moveWith);

	void applyEffect(Player& player) override;

	Card* clone() const override;

};

