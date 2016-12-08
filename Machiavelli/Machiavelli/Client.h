#pragma once
#include <memory>
#include "Socket.h";
#include "Player.h"

using namespace std;

namespace client
{

	void handle(Socket);

	class Client
	{

	public:
		Client(Socket);
		const Player& get_player() const;
		const Socket& get_socket() const;

		void hello();
		const string listen() const;
		void disconnect() const;


	private:
		Socket socket;
		Player player;

	};

}
