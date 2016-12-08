#pragma once
#include "CharacterCard.h"

class Koopman : public CharacterCard
{
public:
	Koopman(int id, string name) : CharacterCard(id, name) {};
	void handle() override;
};
