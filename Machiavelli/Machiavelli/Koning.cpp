#pragma once
#include "Koning.h"

void Koning::handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards)
{

	auto buildings = 0;

	for(auto building : current->get_player().get_buildings())
	{
		if(building->get_color() == "geel")
		{
			current->get_player().add_gold(1);
			buildings++;
		}
	}

	opponent->get_player().setKing(0);
	current->get_player().setKing(1);

	current->write("Je hebt " + std::to_string(buildings) + " goud ontvangen!");
	current->write("Je mag de volgende beurt als eerst beginnen!");
	



}
