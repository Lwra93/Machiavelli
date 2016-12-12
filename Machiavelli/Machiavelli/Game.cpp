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

void Game::run() const
{
	
	sort_age();

	for(auto client : get_clients())
	{
		client->write("\r\nStarting the game! " + get_clients()[0]->get_player().get_name() + " may start.\r\n");
	}

	while(winners.size() < 1)
	{
		
		divide_cards();

	}

	//Karakterkaarten
	//


}

void Game::divide_cards() const
{
	
	random_device dev;
	default_random_engine dre {dev()};
	vector<shared_ptr<CharacterCard>> cards (characterCards.size());
	copy(characterCards.begin(), characterCards.end(), cards.begin());
	shuffle(cards.begin(), cards.end(), dre);
	auto current = get_clients()[0];
	auto other = get_clients()[1];

	current->get_player().flush();
	other->get_player().flush();

	current->write("The first card of the deck has to be discarded. This card is: " + cards[0]->get_name());
	cards.erase(cards.begin());

	while(cards.size() > 0)
	{
		
		other->write("");
		other->write(current->get_player().get_name() + "'s turn. Please wait for his/her decision.");
		string cardNames;
		
		current->write("Your cards: ");
		for(auto card : current->get_player().get_characters())
		{
			current->write("- " + card->get_name());
		}

		current->write("");

		if(cards.size() < 7)
		{
			current->write("Available character cards:");

			for (auto card : cards)
				current->write("- (" + std::to_string(card->get_id()) + ") " + card->get_name());

			current->write("");
			current->writeInput("Please choose a charactercard id to DISCARD> ");
			char c = current->read();
			int id = atoi(&c);

			while (isdigit(id) != 0 || !is_valid_id(cards, id))
			{
				current->writeInput("Please choose a charactercard id to DISCARD> ");
				c = current->read();
				id = atoi(&c);
			}

			auto cardId = get_card_id(cards, id);
			auto card = move(cards.at(cardId));
			cards.erase(cards.begin() + cardId);
			current->write("You have discarded " + card->get_name());
			current->write("");
		}

		current->write("Available character cards:");

		for (auto card : cards)
			current->write("- (" + std::to_string(card->get_id()) + ") " + card->get_name());

		current->write("");
		current->writeInput("Please choose a charactercard id to hold as your own> ");
		char c = current->read();
		int id = atoi(&c);

		while (isdigit(id) != 0 || !is_valid_id(cards, id))
		{
			current->writeInput("Please choose a charactercard id to hold as your own> ");
			c = current->read();
			id = atoi(&c);
		}

		auto cardId = get_card_id(cards, id);
		auto card = move(cards.at(cardId));
		cards.erase(cards.begin() + cardId);

		current->get_player().add_character(move(card));
		
		
		current = (current == get_clients()[0] ? get_clients()[1] : get_clients()[0]);
		other = (other == get_clients()[0] ? get_clients()[1] : get_clients()[0]);

	}



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







