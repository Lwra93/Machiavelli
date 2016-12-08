#pragma once
#include "CharacterCard.h"

class Condottiere : public CharacterCard
{
public:
	Condottiere(int id, string name) : CharacterCard(id, name) {};
	void handle() override;
};
