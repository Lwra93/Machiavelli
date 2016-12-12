#pragma once
#include "PurpleCard.h"

class Laboratorium :
	public PurpleCard
{
public:
	Laboratorium(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Laboratorium();
};

