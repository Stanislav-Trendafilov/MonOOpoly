#pragma once
class Field
{
	size_t fieldId;
public:
	Field(size_t id);
	virtual Field* clone() const=0;
	virtual ~Field()=default;
};

