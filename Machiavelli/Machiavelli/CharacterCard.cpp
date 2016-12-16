#pragma once
#include "CharacterCard.h"

void CharacterCard::kill()
{
	this->dead = true;
}

const bool CharacterCard::isDead() const
{
	return this->dead;
}

void CharacterCard::rob()
{

	this->robbed = true;

}

const bool CharacterCard::isRobbed() const
{
	return this->robbed;
}
