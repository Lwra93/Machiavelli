#pragma once
#include "CharacterCard.h"

class Bouwmeester : public CharacterCard
{
public:
	Bouwmeester(int id, string name) : CharacterCard(id, name) {};
	void handle() override;
};
