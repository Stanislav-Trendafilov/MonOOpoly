#include "VisitField.h"

VisitField::VisitField(int index, MyString name)
	: Field(index, name)
{
}

Field* VisitField::clone() const
{
	return new VisitField(*this);
}
