#pragma once
#include "Game.h"
#include <thread>
#include "config.h"

namespace game
{

	//static map <id, card> building cards
	//static map <id, card> character cards

	void Game::initialise() const
	{

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





