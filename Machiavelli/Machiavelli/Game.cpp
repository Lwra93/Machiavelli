#pragma once
#include "Game.h"
#include <thread>
#include "config.h"
#include <map>
#include "BuildCard.h"
#include "CharacterCard.h"
#include "Factory.h"

namespace game
{

	static map<int, BuildCard> buildCards;
	static map<int, CharacterCard> characterCards;
		//static map <id, card> building cards
		//static map <id, card> character cards

	void Game::initialise() const
	{

		if(characterCards.size() == 0)
			characterCards = move(factory::get_characters("karakterkaarten.csv"));

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
}





