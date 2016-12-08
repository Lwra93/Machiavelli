#pragma once
#include <vector>
#include "CommandHandler.h"
#include "Socket.h"
#include "Client.h"
#include <memory>

using namespace std;

namespace game
{
	class Game
	{

	public:
		void initialise() const;
		void run_server(ServerSocket socket) const;

	private:
		int connected = 0;

	};
}

