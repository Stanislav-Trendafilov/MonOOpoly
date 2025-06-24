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
	size_t getFieldId()const;

	virtual Field* clone() const=0;

	virtual void ApplyAction(Player& player) = 0;

	virtual ~Field()=default;

	virtual void saveToBinary(std::ofstream& ofs) const = 0;
	virtual void loadFromBinary(std::ifstream& ifs) = 0;
};

