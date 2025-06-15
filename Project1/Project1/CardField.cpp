#include "CardField.h"

CardField::CardField(const MyString& name, size_t boardIndex,const MyString& typeOfCard)
	: Field(boardIndex,name)
{
	this->typeOfCard = typeOfCard;

	deck = CardDeck::getInstance();

	deck->InitializeCardDeck();
}

void CardField::ApplyAction(Player& player)
{
	Card* card;

	if (typeOfCard == "chance")
	{
		card = deck->DrawChanceCard();
	}
	else
	{
		card = deck->DrawCommunityChestCard();
	}
	std::cout << card->getName() << std::endl;
	std::cout << card->getEffect() << std::endl;
	card->applyEffect(player);
}

Field* CardField::clone() const
{
	return new CardField(*this);
}

