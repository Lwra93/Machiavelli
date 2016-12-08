#pragma once
#include "CharacterCard.h"

class Koning : public CharacterCard
{
public:
	Koning(int id, string name) : CharacterCard(id, name) {};
	void handle() override;
};
