#pragma once
#include "PurpleCard.h"

class Kerkhof :
	public PurpleCard
{
public:
	Kerkhof(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Kerkhof();
};

