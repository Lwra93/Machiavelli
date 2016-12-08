#pragma once
#include "CharacterCard.h"

class Moordenaar : public CharacterCard
{
public:
	Moordenaar(int id, string name) : CharacterCard(id, name) {};
	void handle() override;
};
