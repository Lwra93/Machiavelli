#pragma once
#include "Moordenaar.h"
#include <algorithm>

void Moordenaar::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> characters, vector<shared_ptr<BuildCard>> availableCards)
{

	current->write("");
	current->write("Wie wil je vermoorden: ");

	for(auto card : characters)
	{
		if (card->get_name() != "Moordenaar")
			current->write("[" + std::to_string(card->get_id()) + "] - " + card->get_name());
	}
	
	
	auto exists = false;
	auto id = current->readnumber();

	while(get_character_by_id(characters,id) == nullptr)
		id = current->readnumber();

	auto character = get_character_by_id(characters, id);
	character->kill();
	current->write(character->get_name() + " was killed!");

}

const shared_ptr<CharacterCard> Moordenaar::get_character_by_id(const vector<shared_ptr<CharacterCard>> cards, const int id) const
{

	for(auto c : cards)
	{
		if (c->get_id() == id && c->get_name() != "Moordenaar")
			return c;
	}

	return nullptr;

}
