#pragma once
#include "Field.h"
#include "MyString.h"
#include "Player.h"

class GoToJailField : public Field
{
	MyString name;

public:
	GoToJailField(const MyString& name,int boardIndex);

	MyString getName() const;
	
	void ApplyAction(Player& player);
	
	Field* clone() const override;
};

