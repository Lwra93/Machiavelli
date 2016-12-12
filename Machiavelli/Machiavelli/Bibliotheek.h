#pragma once
#include "PurpleCard.h"

class Bibliotheek :
	public PurpleCard
{
public:
	Bibliotheek(string name, int value, string color, string description) : PurpleCard(name, value, color, description) {};
	~Bibliotheek();
};

