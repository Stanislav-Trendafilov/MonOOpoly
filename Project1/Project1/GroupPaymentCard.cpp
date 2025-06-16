#include "GroupPaymentCard.h"
#include "Monopoly.h"

GroupPaymentCard::GroupPaymentCard(const MyString& name, const MyString& effect, int paymentAmount)
	: Card(name, effect)
{
	this->paymentAmount = paymentAmount;
}

void GroupPaymentCard::applyEffect(Player& player)
{
	int totalPayment=0;
	MyVector <Player>& players = Monopoly::getInstance()->getPlayers();

	for (size_t i = 0; i < players.size(); i++)
	{
		if (players[i].getPlayerId() != player.getPlayerId())
		{
			players[i].addMoney(paymentAmount);
			totalPayment += paymentAmount;
		}
	}
	player.addMoney((-1)*totalPayment);

	
}

Card* GroupPaymentCard::clone() const
{
	return new GroupPaymentCard(*this);
}


