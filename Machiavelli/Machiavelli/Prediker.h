#pragma once
#include "CharacterCard.h"

class Prediker : public CharacterCard
{
public:
	Prediker(int id, string name) : CharacterCard(id, name) {};
	void handle() override;
};
