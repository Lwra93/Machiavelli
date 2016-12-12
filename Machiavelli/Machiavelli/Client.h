#pragma once
#include <memory>
#include "Socket.h";
#include "Player.h"

using namespace std;

void handle_client(Socket socket);

class Client
{

public:
	Client(Socket);
	Player& get_player();
	const Socket& get_socket() const;

	void hello();
	const string listen() const;
	void write(string line) const;
	void writeInput(string line) const;
	const char Client::read() const;
	const string Client::readline() const;

private:
	Socket socket;
	Player player;

};
