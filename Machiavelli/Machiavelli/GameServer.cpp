#include <iostream>
#include <thread>
#include "GameServer.h"
#include "Game.h"
#include <algorithm>
#include "config.h"


vector<shared_ptr<Client>> clients;

vector<shared_ptr<Client>> get_clients()
{
	return clients;
}

void sort_age()
{

	sort(clients.begin(), clients.end(),
		[](shared_ptr<Client> c1, shared_ptr<Client> c2)
	{
		return c1->get_player().get_age() > c2->get_player().get_age();
	});

}

void sort_king()
{
	sort(clients.begin(), clients.end(),
		[](shared_ptr<Client> c1, shared_ptr<Client> c2)
	{
		return c1->get_player().isKing() > c2->get_player().isKing();
	});
}

void register_client(const shared_ptr<Client> client)
{

	clients.push_back(move(client));

	if (clients.size() == 2)
	{

		Game game;
		game.initialise();
		game.run();

		for(auto client : get_clients())
		{
			
			client->write("Bedankt voor het spelen van Machiavelli. We wachten met smart op de volgende keer!");
			client->close();

		}

		clients.clear();

	}

}

void deregister_client(const shared_ptr<Client> client)
{
	
	if(client != nullptr)
	{
		client->write("Bedankt voor het spelen van Machiavelli. We wachten met smart op de volgende keer!");
		client->close();	
	}
	clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());

	if (clients.size() > 0)
	{
		auto c = clients[0];
		c->write("De andere speler heeft het spel verlaten. Jij wint!");
		c->close();
		clients.clear();
	}
	
}

void writeToAll(const std::string line)
{
	
	for(auto client : get_clients())
	{
		client->write(line);
	}

}

GameServer::GameServer()
{
}


GameServer::~GameServer()
{
}

void GameServer::run(ServerSocket socket) const
{

	cerr << "Server is online on port " + std::to_string(config::port) + "\n";

	while (true) {
		try {
			while (true) {
				cerr << "server listening" << '\n';
				auto client{ socket.accept() };

				thread handler{ handle_client, move(client) };
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



