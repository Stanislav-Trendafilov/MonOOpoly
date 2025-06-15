#pragma once
#include "Field.h"

class VisitField :public Field
{
public:
	VisitField(int index, MyString name);

	void ApplyAction(Player& player) override;

	Field* clone() const override;
};

