#pragma once
#include "Game.h"
#include "Factory.h"
#include "GameServer.h"
#include <algorithm>


void Game::initialise()
{

	factory::initialise();
	characterCards = factory::load_characters();
	buildCards = factory::load_buildings();

}

void Game::run()
{
	
	sort_age();
	random_device dev;
	default_random_engine dre{ dev() };
	vector<shared_ptr<BuildCard>> buildcards(buildCards.size());
	copy(buildCards.begin(), buildCards.end(), buildcards.begin());
	shuffle(buildcards.begin(), buildcards.end(), dre);

	for(auto client : get_clients())
	{
		client->write("\r\nStarting the game! " + get_clients()[0]->get_player().get_name() + " may start.\r\n");
		client->get_player().add_gold(2);
		client->write("Je hebt 2 goud ontvangen.");

		for(auto i = 0; i < 4; i++)
		{
			
			auto building = move(buildcards.at(0));
			client->write("Je hebt [gebouw] " + building->get_name() + " ontvangen.");
			client->get_player().add_building_card(move(building));
			buildcards.erase(buildcards.begin());

		}
		

	}

	while(winners.size() < 1)
	{
		
		divide_cards();
		call_characters(buildcards);

	}

	//Karakterkaarten
	//


}

void Game::divide_cards() const
{

	writeToAll("=== Now starting the card division round. ===");
	
	vector<shared_ptr<CharacterCard>> charcards (characterCards.size());
	random_device dev;
	default_random_engine dre{ dev() };
	copy(characterCards.begin(), characterCards.end(), charcards.begin());
	shuffle(charcards.begin(), charcards.end(), dre);
	
	auto current = get_clients()[0];
	auto other = get_clients()[1];

	current->get_player().flush();
	other->get_player().flush();

	current->write("The first card of the deck has to be discarded. This card is: " + charcards[0]->get_name());
	charcards.erase(charcards.begin());

	while(charcards.size() > 0)
	{
		
		other->write("");
		other->write(current->get_player().get_name() + "'s turn. Please wait for his/her decision.");
		string cardNames;
		
		current->write("Your cards: ");
		for(auto card : current->get_player().get_character_cards())
		{
			current->write("- " + card->get_name());
		}

		current->write("");

		if(charcards.size() < 7)
		{
			current->write("Available character cards:");

			for (auto card : charcards)
				current->write("- (" + std::to_string(card->get_id()) + ") " + card->get_name());

			current->write("");
			current->writeInput("Please choose a charactercard id to DISCARD> ");
			char c = current->read();
			int id = atoi(&c);

			while (isdigit(id) != 0 || !is_valid_id(charcards, id))
			{
				current->writeInput("Please choose a charactercard id to DISCARD> ");
				c = current->read();
				id = atoi(&c);
			}

			auto cardId = get_card_id(charcards, id);
			auto card = move(charcards.at(cardId));
			charcards.erase(charcards.begin() + cardId);
			current->write("You have discarded " + card->get_name());
			current->write("");
		}

		current->write("Available character cards:");

		for (auto card : charcards)
			current->write("- (" + std::to_string(card->get_id()) + ") " + card->get_name());

		current->write("");
		current->writeInput("Please choose a charactercard id to hold as your own> ");
		char c = current->read();
		int id = atoi(&c);

		while (isdigit(id) != 0 || !is_valid_id(charcards, id))
		{
			current->writeInput("Please choose a charactercard id to hold as your own> ");
			c = current->read();
			id = atoi(&c);
		}

		auto cardId = get_card_id(charcards, id);
		auto card = move(charcards.at(cardId));
		charcards.erase(charcards.begin() + cardId);

		current->get_player().add_character_card(move(card));
		
		
		current = (current == get_clients()[0] ? get_clients()[1] : get_clients()[0]);
		other = (other == get_clients()[0] ? get_clients()[1] : get_clients()[0]);

	}

}

void Game::call_characters(vector<shared_ptr<BuildCard>> &buildings)
{
	
	writeToAll("=== Now starting the character round. ===");

	for (auto characterCard : characterCards)
	{

		auto playedFirst = false;
		auto playedSecond = false;
		auto playedFeature = false;

		writeToAll("The king calls forth the " + characterCard->get_name() + "!");

		auto current = who_has_card(characterCard);
		if (current == nullptr)
		{
			writeToAll("The " + characterCard->get_name() + " is absent. Continuing...");
			continue;
		}

		writeToAll(current->get_player().get_name() + " is the " + characterCard->get_name() + "!");

		auto lamb1 = [&]() { play_first(characterCard, buildings, playedFirst, current); };
		auto lamb2 = [&]() { play_second(characterCard, buildings, playedSecond, current); };
		auto lamb3 = [&]() { play_feature(characterCard, buildings, playedFeature, current);  };

		map<int, std::function<void()>> functions;
		functions.emplace(0, lamb1);
		functions.emplace(1, lamb2);
		functions.emplace(2, lamb3);

		while(!playedFirst || !playedSecond || !playedFeature)
		{

			bool choices[] = { playedFirst, playedSecond, playedFeature };
			current->write("Choose one of the following actions: \r\n");

			if(!playedFirst)
				current->write("[0] - Trek bouwkaart / Krijg goud");
			else if(!playedSecond)
				current->write("[1] - Bouwen");

			if (!playedFeature)
				current->write("[2] - Speel eigenschap");

			current->writeInput("> ");
			char choice = current->read();
			current->write("");
			int id = atoi(&choice);

			while(id < 0 || id > 2)
			{
				current->writeInput("> ");
				choice = current->read();
				current->write("");
				id = atoi(&choice);
			}

			auto func = functions.at(id);
			
			func();

			current->write("");

		}

		current->readline();




	}

}

void Game::play_first(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> &buildings, bool& first, shared_ptr<Client> current) const
{
	
	if(first)
	{
		current->write("Deze actie is niet beschikbaar!");
		return;
	}
	
	current->writeInput("Wil je goud innen (0), of bouwkaarten trekken (1)> ");
	char c = current->read();
	current->write("");
	int id = atoi(&c);

	while(id != 0 && id != 1)
	{
		
		current->writeInput("Wil je goud innen (0), of bouwkaarten trekken (1)> ");
		c = current->read();
		current->write("");
		id = atoi(&c);
		
	}

	if(id == 0)
	{
		current->get_player().add_gold(2);
		current->write("Je hebt 2 goud ontvangen.");
		current->write("");
		first = true;
	}
	else
	{
		
		vector<shared_ptr<BuildCard>> drawn;
		auto x = move(buildings.at(0));
		buildings.erase(buildings.begin());
		drawn.push_back(move(x));

		auto y = move(buildings.at(0));
		buildings.erase(buildings.begin());
		drawn.push_back(move(y));

		current->write("Kies een van de volgende bouwkaarten.");
		for(auto i = 0; i < drawn.size(); i++)
		{
			current->write("[" + std::to_string(i) + "] - " + drawn.at(i)->get_name() + " | " + std::to_string(drawn.at(i)->get_value()) + " | " + drawn.at(i)->get_color());
		}

		current->writeInput("> ");
		current->write("");
		char c = current->read();
		int id = atoi(&c);

		while (id != 0 && id != 1)
		{

			current->writeInput("> ");
			c = current->read();
			current->write("");
			id = atoi(&c);

		}

		current->write("Je hebt " + drawn.at(id)->get_name() + " ontvangen!");
		first = true;


	}

}

void Game::play_second(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> &buildings, bool& second, shared_ptr<Client> current) const
{

	if(second)
	{
		current->write("Deze actie is niet beschikbaar!");
		return;
	}
	
	std::string command = "";

	while (true)
	{
		
		current->write("Kies een gebouw om te bouwen (of typ s de bouwronde te stoppen):");
		current->write("Goud: " + std::to_string(current->get_player().get_gold()));
		current->write("Gebouwen:");
		for(auto i = 0; i < current->get_player().get_building_cards().size(); i++)
		{
			auto card = current->get_player().get_building_cards()[i];
			current->write("[" + std::to_string(i) + "] - " + card->get_name() + " | " + std::to_string(card->get_value()) + " | " + card->get_color());
		}
		current->writeInput("Actie> ");
		current->write("");
		char c = current->read();

		if (c == 's')
			break;

		int id = atoi(&c);
		auto chosen = current->get_player().get_building_cards()[id];

		while(chosen == nullptr)
		{
			current->writeInput("Actie> ");
			c = current->read();
			id = atoi(&c);
			chosen = current->get_player().get_building_cards()[id];
		}

		if(chosen->get_value() > current->get_player().get_gold())
		{
			current->write("Dit gebouw is te duur om te bouwen! Je komt " + std::to_string(chosen->get_value() - current->get_player().get_gold()) + " goud te kort.");
		}
		else
		{
			current->write("Je hebt " + std::to_string(chosen->get_value()) + " betaald en " + chosen->get_name() + " gebouwd!");
			auto card = move(chosen);
			current->get_player().add_gold(-(card->get_value()));
			current->get_player().add_building(move(card));
			current->get_player().remove_building_card(move(id));
		}

	}

	second = true;



}

void Game::play_feature(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> &buildings, bool& feature, shared_ptr<Client> current) const
{

	if(feature)
	{
		current->write("Deze actie is niet beschikbaar!");
		return;
	}
	
	


}

shared_ptr<Client> Game::who_has_card(const shared_ptr<CharacterCard> card)
{
	
	for(auto c1 : get_clients()[0]->get_player().get_character_cards())
	{
		if (c1->get_id() == card->get_id())
			return get_clients()[0];
	}

	for (auto c2 : get_clients()[1]->get_player().get_character_cards())
	{
		if (c2->get_id() == card->get_id())
			return get_clients()[1];
	}

	return nullptr;

}



const bool Game::is_valid_id(const vector<shared_ptr<CharacterCard>> cards, int id) const
{

	auto x = id;

	for(auto card : cards)
	{
		if (card->get_id() == id)
			return true;
	}
	return false;

}

const int Game::get_card_id(const vector<shared_ptr<CharacterCard>> &cards, int id) const
{
	
	auto index = 99;

	for(auto i = 0; i < cards.size(); i++)
	{
		if(cards.at(i)->get_id() == id)
		{
			index = i;
			break;
		}
	}

	return index;

}







