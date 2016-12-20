#pragma once
#include "Condottiere.h"

void Condottiere::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards)
{

	auto buildings = 0;

	for (auto building : current->get_player().get_buildings())
	{
		if (building->get_color() == "rood")
		{
			current->get_player().add_gold(1);
			buildings++;
		}
	}

	current->write("Je hebt " + std::to_string(buildings) + " goud ontvangen!");

	current->write("");
	auto prediker = false;

	for(auto card : opponent->get_player().get_character_cards())
	{
		if (card->get_name() == "Prediker")
			prediker = true;
	}

	if (opponent->get_player().get_buildings().size() > 7)
	{
		current->write(opponent->get_player().get_name() + " heeft al " + std::to_string(opponent->get_player().get_buildings().size()) + " gebouwen. Je mag niks meer verwijderen!");
	}
	else if (prediker)
		current->write(opponent->get_player().get_name() + " is de Prediker! Je kan zijn/haar gebouwen niet verwoesten.");
	else
	{
		current->write("Welk gebouw van " + opponent->get_player().get_name() + " wil je verwijderen:");

		for (int i = 0; i < opponent->get_player().get_buildings().size(); i++)
		{
			auto building = opponent->get_player().get_buildings()[i];
			current->write("[" + std::to_string(i) + "] - " + building->get_name() + " | " + building->get_color() + " | Kost om te verwijderen: " + std::to_string(building->get_value() - 1));
		}

		while(true)
		{
			int chosen = -1;
			while (chosen < 0 || chosen >= opponent->get_player().get_buildings().size())
			{

				current->writeInput("> ");
				string c = current->readline();
				if (c == "s")
					break;

				chosen = stoi(c);

			}

			if (chosen < 0 || chosen >= opponent->get_player().get_buildings().size())
			{
				auto cost = opponent->get_player().get_buildings().at(chosen)->get_value() - 1;
				if (current->get_player().get_gold() >= cost)
				{
					current->get_player().add_gold(-cost);
					current->write("Je hebt " + std::to_string(cost) + " betaald en de " + opponent->get_player().get_buildings().at(chosen)->get_name() + " verwoest!");
					opponent->get_player().get_buildings().erase(opponent->get_player().get_buildings().begin() + chosen);
					break;
				}
				else
				{
					current->write("Je kunt dit niet betalen!");
				}

			}
		}

		

	}

	

}
