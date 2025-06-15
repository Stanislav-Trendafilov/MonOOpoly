#pragma once
#include "Card.h"

class MoveToNearestStationCard	:public Card
{
public:
	MoveToNearestStationCard(const MyString& name, const MyString& effect);

	void applyEffect(Player& player) override;

	Card* clone() const override;
};

