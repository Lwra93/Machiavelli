#pragma once
#include "CharacterCard.h"

class Moordenaar : public CharacterCard
{
public:
	Moordenaar(int id, string name) : CharacterCard(id, name) {};
	void handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards) override;
	const shared_ptr<CharacterCard> get_character_by_id(const vector<shared_ptr<CharacterCard>>, const int) const;
};
