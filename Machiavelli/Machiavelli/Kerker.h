#pragma once
#include "PurpleCard.h"

class Kerker :
	public PurpleCard
{
public:
	Kerker(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Kerker();
};

