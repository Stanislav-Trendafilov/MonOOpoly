#pragma once
#include "MyString.h"

class Player;

class Field
{
	MyString name;
	size_t fieldId;
public:
	Field() = default;
	Field(size_t id,const MyString& name);
	MyString getName() const;

	virtual Field* clone() const=0;

	virtual void ApplyAction(Player& player) = 0;

	virtual ~Field()=default;
};

