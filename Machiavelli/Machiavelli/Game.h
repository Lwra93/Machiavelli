#pragma once
#include <vector>
#include "CommandHandler.h"
#include "Socket.h"
#include "Client.h"
#include <memory>
#include <map>
#include "BuildCard.h"
#include "CharacterCard.h"

using namespace std;

class Game
{

public:
	void initialise();
	void run_server(ServerSocket socket) const;

	CharacterCard get_card(string name);
	CharacterCard get_card(int id);

private:
	vector<BuildCard> buildCards;
	vector<CharacterCard> characterCards;

};

