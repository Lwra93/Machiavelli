#include "PurpleCard.h"



PurpleCard::PurpleCard(string name, int id, string color, string description) : BuildCard(name, id, color)
{
	this->description = description;
}


PurpleCard::~PurpleCard()
{
}
