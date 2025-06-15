#pragma once
#include "Card.h"
#include <iostream>

class MoveToLocationCard :public Card
{
	size_t indexOfLocation;
public:
	MoveToLocationCard(const MyString& name, const MyString& effect, size_t indexOfLocation);

	void applyEffect(Player& player) override;

	Card* clone() const override;

};

