#pragma once
#include "Koopman.h"

void Koopman::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards)
{

	auto buildings = 0;

	for (auto building : current->get_player().get_buildings())
	{
		if (building->get_color() == "groen")
		{
			current->get_player().add_gold(1);
			buildings++;
		}
	}

	current->get_player().add_gold(1);

	current->write("Je hebt " + std::to_string(buildings) + " goud ontvangen, plus 1 vanwege koopkracht!");

}
