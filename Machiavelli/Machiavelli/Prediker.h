#pragma once
#include "CharacterCard.h"

class Prediker : public CharacterCard
{
public:
	Prediker(int id, string name) : CharacterCard(id, name) {};
	void handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards) override;
};
