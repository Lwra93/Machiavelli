#pragma once
#include "Game.h"
#include <thread>
#include "config.h"
#include <map>
#include "BuildCard.h"
#include "CharacterCard.h"
#include "Factory.h"


void Game::initialise()
{

	characterCards = move(factory::get_characters(config::characterCardsLocation));
	//buildCards = move(factory::get_buildings(config::buildingCardsLocation));

	thread consumer(commands::consume);
	ServerSocket socket{ config::port };
	this->run_server(move(socket));
	consumer.join();

}

void Game::run_server(ServerSocket server) const
{

	while (true) {
		try {
			while (true) {
				cerr << "server listening" << '\n';
				auto client{ server.accept() };

				thread handler{ client::handle, move(client) };
				handler.detach();
			}
		}
		catch (const exception& ex) {
			cerr << ex.what() << ", resuming..." << '\n';
		}
		catch (...) {
			cerr << "problems, problems, but: keep calm and carry on!\n";
		}
	}
}

CharacterCard Game::get_card(string name)
{
	for(auto card : characterCards)
	{
		if (card.get_name() == name)
			return card;
	}
	
}

CharacterCard Game::get_card(int id)
{
	
}







