#pragma once
#include "Card.h"


class MoveToNearestUtilCard :public Card
{
public:
	MoveToNearestUtilCard(const MyString& name, const MyString& effect);

	void applyEffect(Player& player) override;

	Card* clone() const override;

};

