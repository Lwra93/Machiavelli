#pragma once
#include "PurpleCard.h"

class Werkplaats :
	public PurpleCard
{
public:
	Werkplaats(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Werkplaats();
};

