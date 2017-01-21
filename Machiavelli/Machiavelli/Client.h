#pragma once
#include <memory>
#include "Socket.h"
#include "Player.h"

using namespace std;

void handle_client(Socket socket);

class Client : public std::enable_shared_from_this<Client>
{

public:
	Client(Socket);
	Player& get_player();
	const Socket& get_socket() const;

	void hello();
	const string listen();
	void write(string line) const;
	void writeInput(string line) const;
	const string Client::readline();
	const int Client::readnumber();

	void close();

private:
	Socket socket;
	Player player;

};
