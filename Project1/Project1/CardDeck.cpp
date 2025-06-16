#include "CardDeck.h"

CardDeck::CardDeck() {
	InitializeCardDeck();
	ShuffleDecks();
}

CardDeck* CardDeck::instance = nullptr;

CardDeck* CardDeck::getInstance() {
	if (!instance) {
		instance = new CardDeck();
	}
	return instance;
}

void CardDeck::InitializeCardDeck() 
{
	chanceCards.addObject(new MoveToLocationCard("?Chance?", "Move to Rila Monastery", 39));

	chanceCards.addObject(new MoveToLocationCard("?Chance?", "Advance to Go (Collect 200$)", 0));

	chanceCards.addObject(new MoveToLocationCard("?Chance?", "Advance to Slaveykov Square. If you pass Go, collect $200.", 11));

	chanceCards.addObject(new MoveToLocationCard("?Chance?", "Advance to National Palace of Culture", 21));

	chanceCards.addObject(new MoveToNearestStationCard("?Chance?", "Advance to the nearest Railroad. If unowned, you may buy it from the Bank."));

	chanceCards.addObject(new MoveToNearestStationCard("?Chance?", "Advance to the nearest Railroad. If unowned, you may buy it from the Bank."));

	chanceCards.addObject(new MoveToNearestUtilCard("?Chance?", "Advance to the nearest Utility"));
	
	chanceCards.addObject(new MoveToNearestUtilCard("?Chance?", "Advance to the nearest Utility"));

	chanceCards.addObject(new PaymentCard("?Chance?", "Bank pays you dividend of $50.", 50));

	chanceCards.addObject(new MovePositionCard("?Chance?", "Go back 3 spaces.", -3));

	chanceCards.addObject(new MoveToLocationCard("?Chance?", "Go to Jail. Go directly to Jail, do not pass Go, do not collect $200.", 30));

	chanceCards.addObject(new PaymentCard("?Chance?", "Speeding fine $15.", -15));

	chanceCards.addObject(new MoveToLocationCard("?Chance?", "Take a trip to Burgas Station", 5));

	chanceCards.addObject(new GroupPaymentCard("?Chance?", "You have been elected Chairman of the Board. Pay each player $50.", 50));

	chanceCards.addObject(new MoveToLocationCard("?Chance?", "Take a trip to Varna Station", 25));


	communityChestCards.addObject(new MoveToLocationCard("?Community Chest?", "Advance to Go (Collect $200)", 0));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "Bank error in your favor. Collect $200", 200));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "Doctor’s fee. Pay $50", -50));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "From sale of stock you get $50", 50));

	communityChestCards.addObject(new MoveToLocationCard("?Community Chest?", "Go to Jail. Go directly to Jail, do not pass Go, do not collect $200.", 30));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "Holiday fund matures. Receive $100", 100));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "Income tax refund. Collect $20", 20));

	communityChestCards.addObject(new GroupPaymentCard("?Community Chest?", "It is your birthday.Collect $10 from every player", -10));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "Life insurance matures. Collect $100", 100));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "Pay hospital fees of $100", -100));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "Pay school fees of $50", -50));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "Receive $25 consultancy fee", 25));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "You have won second prize in a beauty contest. Collect $10", 10));

	communityChestCards.addObject(new PaymentCard("?Community Chest?", "You inherit $100", 100));


}

void CardDeck::destroyInstance()
{
	delete instance;
	instance = nullptr;
}

void CardDeck::ShuffleDecks()
{
	std::srand(std::time(NULL)); 

	for (size_t i = 0; i < chanceCards.getSize(); ++i)
	{
		size_t j = rand() % chanceCards.getSize();
		chanceCards.swap(i, j); 
	}

	for (size_t i = 0; i < communityChestCards.getSize(); ++i)
	{
		size_t j = rand() % communityChestCards.getSize();
		communityChestCards.swap(i, j);
	}

	chanceIndex = 0;
	communityIndex = 0;
}

Card* CardDeck::DrawChanceCard()
{
	if (chanceCards.getSize() == 0) return nullptr;
	Card* card = chanceCards[chanceIndex];
	chanceIndex = (chanceIndex + 1) % chanceCards.getSize();
	return card;
}

Card* CardDeck::DrawCommunityChestCard()
{
	if (communityChestCards.getSize() == 0) return nullptr;
	Card* card = communityChestCards[communityIndex];
	communityIndex = (communityIndex + 1) % communityChestCards.getSize();
	return card;
}