#pragma once
#include "PurpleCard.h"

class Universiteit :
	public PurpleCard
{
public:
	Universiteit(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Universiteit();
};

