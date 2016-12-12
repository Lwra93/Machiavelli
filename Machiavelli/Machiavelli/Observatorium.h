#pragma once
#include "PurpleCard.h"

class Observatorium :
	public PurpleCard
{
public:
	Observatorium(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Observatorium();
};

