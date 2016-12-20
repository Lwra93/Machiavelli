#pragma once
#include "Socket.h"
#include "Client.h"
#include <vector>
#include "Game.h"

using namespace std;

vector<shared_ptr<Client>> get_clients();
void sort_age();
void sort_king();
void register_client(const shared_ptr<Client> client);
void deregister_client(const shared_ptr<Client> client);
void writeToAll(const std::string line);

class GameServer
{
public:
	GameServer();
	~GameServer();
	void run(ServerSocket socket) const;
	
};
