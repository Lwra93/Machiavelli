#pragma once
#include "Prediker.h"

void Prediker::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards)
{

	current->write("");
	current->write("===== Acties: Prediker =====");
	auto buildings = 0;

	for (auto building : current->get_player().get_buildings())
	{
		if (building->get_color() == "blauw")
		{
			current->get_player().add_gold(1);
			buildings++;
		}
	}

	current->write("Je hebt " + std::to_string(buildings) + " goud ontvangen voor elk blauw gebouw!");

}
