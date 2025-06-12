#pragma once
#include "Field.h"
#include "MyString.h"
#include "Player.h"

class GoToJailField : public Field
{
public:
	GoToJailField(const MyString& name,int boardIndex);
	
	void ApplyAction(Player& player);
	
	Field* clone() const override;
};

