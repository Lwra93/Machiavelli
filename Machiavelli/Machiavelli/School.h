#pragma once
#include "PurpleCard.h"

class School :
	public PurpleCard
{
public:
	School(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~School();
};

