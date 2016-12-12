#pragma once
#include "PurpleCard.h"

class Hof :
	public PurpleCard
{
public:
	Hof(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Hof();
};

