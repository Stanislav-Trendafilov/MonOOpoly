#pragma once
#include "Card.h"

class Monopoly;

class GroupPaymentCard : public Card
{
	int paymentAmount;
public:
	GroupPaymentCard(const MyString& name, const MyString& effect, int paymentAmount);

	void applyEffect(Player& player) override;

	Card* clone() const override;
};

