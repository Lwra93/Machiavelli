#pragma once
#include "Magier.h"

void Magier::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards)
{

	current->write("");
	current->write("Wat wil je doen?\r\n[0] - Alle bouwkaarten ruilen met andere speler\r\n[1] - Bouwkaarten afleggen en opnieuw trekken");

	
	std::string c;
	int choice = -1;

	while(choice != 0 && choice != 1)
	{
		current->writeInput("> ");
		c = current->readline();
		choice = stoi(c);
		current->write("");
	}

	if (choice == 0)
	{

		auto currentCards = move(current->get_player().get_building_cards());
		auto opponentCards = move(opponent->get_player().get_building_cards());

		current->get_player().set_building_cards(move(opponentCards));
		opponent->get_player().set_building_cards(move(currentCards));
		
		current->write("Je bent je eigen bouwkaarten kwijt en hebt de bouwkaarten van " + opponent->get_player().get_name() + " gekregen!");
		opponent->write("Je bent je eigen bouwkaarten kwijt en hebt de bouwkaarten van " + current->get_player().get_name() + " gekregen!");

	}
	else
	{
		
		auto amountOfCards = current->get_player().get_building_cards().size();
		current->get_player().get_building_cards().clear();

		for(auto i = 0; i < amountOfCards; i++)
		{
			
			auto card = move(availableCards.at(0));
			availableCards.erase(availableCards.begin());
			current->get_player().add_building_card(move(card));

		}

		current->write("Je hebt je eigen bouwkaarten weggegooit en je hebt " + std::to_string(amountOfCards) + " kaarten bijgetrokken!");

	}




}
