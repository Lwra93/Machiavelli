#pragma once
#include "CharacterCard.h"

void CharacterCard::reset()
{

	this->dead = false;
	this->robbed = false;

}

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

std::ostream& operator<<(std::ostream& out, const shared_ptr<CharacterCard> card)
{

	out << "Name: ";
	out << card->get_name();

	return out;

}