#pragma once
#include "Field.h"
#include "Player.h"

class PayFieldTax:public Field
{
	int fieldTax;
public:
	PayFieldTax(const MyString& name, int boardIndex,int tax);

	void ApplyAction(Player& player);

	Field* clone() const override;

};

