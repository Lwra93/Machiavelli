#pragma once
#include "BuildCard.h"
class PurpleCard :
	public BuildCard
{
public:
	PurpleCard(string name, int value, string color, string description);
	~PurpleCard();

private:
	string description;

};

