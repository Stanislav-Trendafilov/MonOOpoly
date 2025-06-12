#include "Field.h"

Field::Field(size_t id,const MyString& name)
{
	this->fieldId = id;
	this->name = name;
}

MyString Field::getName() const
{
	return this->name;
}
