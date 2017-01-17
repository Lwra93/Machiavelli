#pragma once
#include "Game.h"
#include "Factory.h"
#include "GameServer.h"
#include <algorithm>


Game::~Game()
{

	characterCards.clear();
	buildCards.clear();

}

void Game::initialise()
{

	factory::initialise();
	characterCards = factory::load_characters();
	buildCards = factory::load_buildings();

}

void Game::run()
{
	
	sort_age();
	get_clients()[0]->get_player().setKing(1);
	get_clients()[1]->get_player().setKing(0);
	random_device dev;
	default_random_engine dre{ dev() };
	vector<shared_ptr<BuildCard>> buildcards(buildCards.size());
	copy(buildCards.begin(), buildCards.end(), buildcards.begin());
	shuffle(buildcards.begin(), buildcards.end(), dre);

	for(auto client : get_clients())
	{
		client->write("");
		client->write("\r\We beginnen het spel! " + get_clients()[0]->get_player().get_name() + " mag beginnen.\r\n");
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
	
		sort_king();
	
		divide_cards();
		call_characters(buildcards);

	}

	vector<int> points;
	for(auto client : get_clients())
		points.push_back(calculate_score(client));

	if(points[0] == points[1])
	{
		points.clear();
		for (auto client : get_clients())
			points.push_back(calculate_no_bonus(client));
	}

	int id = (points[0] > points[1] ? 0 : 1);
	writeToAll("");
	writeToAll(get_clients()[0]->get_player().get_name() + ": " + std::to_string(points[0]) + " punten.");
	writeToAll(get_clients()[1]->get_player().get_name() + ": " + std::to_string(points[1]) + " punten.");
	writeToAll("");
	writeToAll("Het spel is afgelopen! " + get_clients()[id]->get_player().get_name() + " heeft gewonnen!");
	writeToAll("");

}

void Game::divide_cards()
{

	writeToAll("");
	writeToAll("=== Nu begint de karakterronde. ===");
	
	discardedCharacters.clear();

	for (auto card : characterCards)
		card->reset();

	vector<shared_ptr<CharacterCard>> charcards (characterCards.size());
	random_device dev;
	default_random_engine dre{ dev() };
	copy(characterCards.begin(), characterCards.end(), charcards.begin());
	shuffle(charcards.begin(), charcards.end(), dre);
	
	auto current = get_clients()[0];
	auto other = get_clients()[1];

	current->get_player().flush();
	other->get_player().flush();

	current->write("");
	current->write("De eerste kaart in de stapel wordt weggegooid. Deze kaart is: " + charcards[0]->get_name());
	current->write("");

	auto card = move(charcards.at(0));
	charcards.erase(charcards.begin());
	discardedCharacters.push_back(move(card));

	while(charcards.size() > 0)
	{
		
		other->write("");
		other->write(current->get_player().get_name() + "'s beurt. Wacht alstublieft op zijn/haar beurt.");
		string cardNames;
		
		current->write("===== Kies een karakterkaart =====");
		current->write("Je kaarten: ");
		for(auto card : current->get_player().get_character_cards())
		{
			current->write("- " + card->get_name());
		}

		current->write("");

		if(charcards.size() < 7)
		{
			current->write("Beschikbare karakterkaarten:");

			for (auto card : charcards)
				current->write("- (" + std::to_string(card->get_id()) + ") " + card->get_name());

			current->write("");
			current->writeInput("Kies een karakterkaart om te VERWIJDEREN:");
			auto id = current->readnumber();

			while (!is_valid_id(charcards, id))
				id = current->readnumber();

			auto cardId = get_card_id(charcards, id);
			auto card = move(charcards.at(cardId));
			charcards.erase(charcards.begin() + cardId);
			current->write("Je hebt " + card->get_name() + " verwijderd.");
			current->write("");
			discardedCharacters.push_back(move(card));
		}

		current->write("Beschikbare karakterkaarten:");

		for (auto card : charcards)
			current->write("- (" + std::to_string(card->get_id()) + ") " + card->get_name());

		current->write("");
		current->writeInput("Kies een karakterkaart om zelf te houden:");
		auto id = current->readnumber();

		while (!is_valid_id(charcards, id))
			id = current->readnumber();

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
	
	writeToAll("");
	writeToAll("=== Nu begint de actieronde. ===");

	for (auto characterCard : characterCards)
	{

		if(characterCard->isDead())
		{
			writeToAll("De koning roept de " + characterCard->get_name() + " op, maar hij/zij is helaas vermoord.");
			continue;
		}
		writeToAll("De koning roept de " + characterCard->get_name() + " op!");

		auto current = who_has_card(characterCard);
		if (current == nullptr)
		{
			writeToAll("De " + characterCard->get_name() + " is absent. We gaan door...");
			continue;
		}
		writeToAll(current->get_player().get_name() + " is de " + characterCard->get_name() + "!");

		if(characterCard->isRobbed())
		{
			auto card = get_character_by_name("Dief");
			auto receiver = who_has_card(card);

			auto gold = current->get_player().get_gold();
			receiver->get_player().add_gold(gold);
			current->get_player().add_gold(-gold);

			writeToAll("De " + characterCard->get_name() + " was bestolen! Al " + current->get_player().get_name() + "'s geld gaat naar " + receiver->get_player().get_name());
		}

		auto playedFirst = false;
		auto playedSecond = false;
		auto playedFeature = false;

		auto lamb1 = [&]() { play_first(characterCard, buildings, playedFirst, current); };
		auto lamb2 = [&]() { play_second(characterCard, buildings, playedSecond, current); };
		auto lamb3 = [&]() { play_feature(characterCard, buildings, playedFeature, current);  };

		map<int, std::function<void()>> functions;
		functions.emplace(0, lamb1);
		functions.emplace(1, lamb2);
		functions.emplace(2, lamb3);

		print_buildings(current);

		while(!playedFirst || !playedSecond || !playedFeature)
		{

			current->write("==== Acties ====");
			bool choices[] = { playedFirst, playedSecond, playedFeature };
			current->write("Kies een van de volgende acties: \r\n");

			if(!playedFirst)
				current->write("[0] - Trek bouwkaart / Krijg goud");
			else if(!playedSecond)
				current->write("[1] - Bouwen");

			if (!playedFeature)
				current->write("[2] - Speel eigenschap");

			auto id = current->readnumber();

			while(id < 0 || id > 2)
				id = current->readnumber();

			auto performTurn = functions.at(id);
			performTurn();

			current->write("");

		}

	}

}

void Game::play_first(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> buildings, bool& first, shared_ptr<Client> current) const
{
	
	if(first)
	{
		current->write("Deze actie is niet beschikbaar!");
		return;
	}
	
	current->writeInput("Wil je goud innen (0), of bouwkaarten trekken (1)");
	auto id = current->readnumber();

	while(id != 0 && id != 1)
		id = current->readnumber();

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

		auto id = current->readnumber();

		while (id != 0 && id != 1)
			id = current->readnumber();

		current->write("Je hebt " + drawn.at(id)->get_name() + " ontvangen!");
		first = true;


	}

}

void Game::play_second(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> buildings, bool& second, shared_ptr<Client> current)
{

	if(second)
	{
		current->write("Deze actie is niet beschikbaar!");
		return;
	}
	
	auto built = 0;
	auto maxBuilt = (currentCard == get_character_by_name("Bouwmeester") ? 3 : 1);

	while (built < maxBuilt)
	{
		
		current->write("Kies een gebouw om te bouwen (of typ s de bouwronde te stoppen):");
		current->write("Goud: " + std::to_string(current->get_player().get_gold()));
		current->write("Gebouwen:");
		for(auto i = 0; i < current->get_player().get_building_cards().size(); i++)
		{
			auto card = current->get_player().get_building_cards()[i];
			current->write("[" + std::to_string(i) + "] - " + card->get_name() + " | " + std::to_string(card->get_value()) + " | " + card->get_color());
		}

		std::string c = current->readline();

		if (c == "s")
			break;

		try
		{
			auto choice = stoi(c);

			if(choice < 0 || choice >= current->get_player().get_building_cards().size())
			{
				current->write("Dit gebouw bestaat niet!");
				continue;
			}

			auto chosen = current->get_player().get_building_cards()[choice];
			if (chosen == nullptr)
				current->write("Dit gebouw bestaat niet!");
			else
			{
				if (chosen->get_value() > current->get_player().get_gold())
				{
					current->write("Dit gebouw is te duur om te bouwen! Je komt " + std::to_string(chosen->get_value() - current->get_player().get_gold()) + " goud te kort.");
				}
				else
				{
					current->write("Je hebt " + std::to_string(chosen->get_value()) + " betaald en " + chosen->get_name() + " gebouwd!");
					auto card = move(chosen);
					current->get_player().add_gold(-(card->get_value()));
					current->get_player().add_building(move(card));
					current->get_player().remove_building_card(move(choice));
					built++;
				}
			}
		} catch(...)
		{
			current->write("Dit gebouw bestaat niet!");
		}

	}

	auto b = current->get_player().get_buildings();
	if(b.size() > 7 && std::find(winners.begin(), winners.end(), current) == winners.end())
	{
		winners.push_back(current);
	}

	second = true;



}

void Game::play_feature(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> buildings, bool& feature, shared_ptr<Client> current) const
{

	if(feature)
	{
		current->write("Deze actie is niet beschikbaar!");
		return;
	}

	shared_ptr<Client> opponent = (get_clients()[0] == current ? get_clients()[1] : get_clients()[0]);
	std::vector<shared_ptr<CharacterCard>> list;

	for (auto card : current->get_player().get_character_cards())
		list.push_back(card);

	for (auto card : opponent->get_player().get_character_cards())
		list.push_back(card);

	for (auto card : discardedCharacters)
		list.push_back(card);

	sort(list.begin(), list.end(), [](shared_ptr<CharacterCard> c1, shared_ptr<CharacterCard> c2)
	{
		return c1->get_id() < c2->get_id();
	});

	currentCard->handle(current, opponent, list, buildings);


	feature = true;
	
	


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

const shared_ptr<CharacterCard> Game::get_character_by_name(const std::string name) const
{
	
	for (auto c1 : get_clients()[0]->get_player().get_character_cards())
	{
		if (c1->get_name() == name)
			return c1;
	}

	for (auto c2 : get_clients()[1]->get_player().get_character_cards())
	{
		if (c2->get_name() == name)
			return c2;
	}

	for(auto c3 : discardedCharacters)
	{
		if (c3->get_name() == name)
			return c3;
	}


	//should not happen
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

const int Game::get_card_id(const vector<shared_ptr<CharacterCard>> cards, int id) const
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

const int Game::calculate_score(const shared_ptr<Client> client) const
{

	vector<string> colors;
	auto points = 0;

	for(auto building : client->get_player().get_buildings())
	{
		points += building->get_value();
		if(std::find(colors.begin(), colors.end(), building->get_color()) != colors.end() && building->get_color() != "lila")
		{
			colors.push_back(building->get_color());
		}
	}

	if (colors.size() == 5)
		points += 3;
		
	if (winners.size() > 0 && winners[0] == client)
		points += 4;
	else if (winners.size() > 1 && winners[1] == client)
		points += 2;
	
	return points;
}

const int Game::calculate_no_bonus(const shared_ptr<Client> client) const
{
	auto points = 0;

	for (auto building : client->get_player().get_buildings())
		points += building->get_value();

	return points;
}

void Game::print_buildings(const shared_ptr<Client> current) const
{

	current->write("");

	for(auto client : get_clients())
	{
		
		current->write("==== " + client->get_player().get_name() + "'s gebouwen ====");
		for(auto building : client->get_player().get_buildings())
			current->write("- Naam: " + building->get_name() + ", Waarde: " + std::to_string(building->get_value()) + ", Kleur: " + building->get_color());

	}

	current->write("");

}







