#pragma once
#include "Bouwmeester.h"

void Bouwmeester::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards)
{

	current->write("");
	current->write("===== Acties: Bouwmeester =====");
	
	for(auto i = 0; i < 2; i++)
	{
		
		auto card = move(availableCards.at(0));
		availableCards.erase(availableCards.begin());
		current->get_player().add_building_card(move(card));

	}

	current->write("Je hebt twee gebouwen ontvangen!");

}
