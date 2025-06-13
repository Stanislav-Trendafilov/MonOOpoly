#include "PaymentCard.h"

PaymentCard::PaymentCard(const MyString& name, const MyString& effect, int paymentAmount)
	:Card(name, effect)
{
	this->paymentAmount = paymentAmount;
}

void PaymentCard::applyEffect(Player& player)
{
	player.addMoney(paymentAmount);
}

Card* PaymentCard::clone()const
{
	return new PaymentCard(*this);
}