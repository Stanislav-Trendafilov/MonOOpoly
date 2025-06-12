#pragma once
#include "Field.h"

class VisitField :public Field
{
public:
	VisitField(int index, MyString name);

	Field* clone() const override;
};

