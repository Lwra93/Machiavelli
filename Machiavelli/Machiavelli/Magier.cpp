#pragma once
#include "Magier.h"

void Magier::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards)
{

	current->write("");
	current->write("===== Acties: Magier =====");
	current->write("Wat wil je doen?\r\n[0] - Alle bouwkaarten ruilen met andere speler\r\n[1] - Bouwkaarten afleggen en opnieuw trekken");

	
	auto choice = current->readnumber();

	while (choice != 0 && choice != 1)
		choice = current->readnumber();

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
		auto done = false;
		auto removedCards = 0;

		while(!done)
		{

			current->write("Deze kaarten heb je nu in bezit, welke wil je inleveren? (als je klaar bent gebruik s om te stoppen)");
			for (auto i = 0; i < current->get_player().get_building_cards().size(); i++)
			{
				current->write("[" + to_string(i) + "] - " + current->get_player().get_building_cards().at(i)->get_name());
			}

			string input = current->readline();
			int c = -1;

			if(input == "s")
				done = true;
			else
			{
				try
				{
					c = stoi(input);

					if(c >= 0 && c < current->get_player().get_building_cards().size())
					{
						current->get_player().remove_building_card(c);
						removedCards++;
					}
	
				}
				catch (...)
				{

				}
			}
				

			if (current->get_player().get_building_cards().size() == 0)
				break;


		}
		

		for(auto i = 0; i < removedCards; i++)
		{
			
			auto card = move(availableCards.at(0));
			availableCards.erase(availableCards.begin());
			current->get_player().add_building_card(move(card));

		}

		current->write("Je hebt " + std::to_string(removedCards) + " bouwkaarten weggegooit en je hebt " + std::to_string(removedCards) + " kaarten bijgetrokken!");

	}




}
