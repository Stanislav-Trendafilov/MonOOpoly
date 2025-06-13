#pragma once
#include "Card.h"

class PaymentCard :public Card
{
	int paymentAmount;
public:
	PaymentCard(const MyString& name, const MyString& effect, int paymentAmount);

	void applyEffect(Player& player) override;

	Card* clone() const override;
};

