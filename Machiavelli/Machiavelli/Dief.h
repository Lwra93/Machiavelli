#pragma once
#include "CharacterCard.h"

class Dief : public CharacterCard
{
public:
	Dief(int id, string name) : CharacterCard(id, name) {};
	void handle() override;
};
