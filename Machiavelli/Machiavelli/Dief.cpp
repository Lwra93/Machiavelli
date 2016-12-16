#pragma once
#include "Dief.h"

void Dief::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> characters, vector<shared_ptr<BuildCard>> availableCards)
{

	current->write("");
	current->write("Wie wil je bestelen: ");

	for (auto card : characters)
	{
		if (card->get_name() != "Moordenaar" && card->get_name() != "Dief" && !card->isDead())
			current->write("[" + std::to_string(card->get_id()) + "] - " + card->get_name());
	}

	auto exists = false;
	std::string c;
	int id = -1;

	while (get_character_by_id(characters, id) == nullptr)
	{
		current->writeInput("> ");
		c = current->readline();
		id = stoi(c);
		current->write("");
	}

	auto character = get_character_by_id(characters, id);
	character->rob();
	current->write(character->get_name() + " was bestolen!");


}

const shared_ptr<CharacterCard> Dief::get_character_by_id(const vector<shared_ptr<CharacterCard>> cards, const int id) const
{

	for (auto c : cards)
	{
		if (c->get_id() == id && c->get_name() != "Moordenaar" && c->get_name() != "Dief" && !c->isDead())
			return c;
	}

	return nullptr;

}
