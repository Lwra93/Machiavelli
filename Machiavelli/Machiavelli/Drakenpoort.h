#pragma once
#include "PurpleCard.h"

class Drakenpoort :
	public PurpleCard
{
public:
	Drakenpoort(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Drakenpoort();
};

