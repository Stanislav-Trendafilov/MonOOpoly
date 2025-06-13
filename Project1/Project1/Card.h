#pragma once
#include "MyString.h"
#include "Player.h"

class Card
{
	MyString name;
	MyString effect;
public:
	Card() = default;
	Card(const MyString& name, const MyString& effect);
	MyString getName() const;
	MyString getEffect() const;

	virtual void applyEffect(Player& player) = 0;

	virtual Card* clone() const = 0;
	virtual ~Card() = default;
};

