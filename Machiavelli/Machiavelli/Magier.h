#pragma once
#include "CharacterCard.h"

class Magier : public CharacterCard
{
public:
	Magier(int id, string name) : CharacterCard(id, name) {};
	void handle() override;
};
