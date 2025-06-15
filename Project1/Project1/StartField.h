#pragma once
#include "Field.h"
#include "Player.h"

class StartField :public Field
{
	int fieldIncome;
public:
	StartField(const MyString& name, int boardIndex, int fieldIncome);

	void ApplyAction(Player& player) override;

	Field* clone() const override;

};


