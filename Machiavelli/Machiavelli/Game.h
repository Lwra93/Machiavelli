#pragma once
#include <vector>
#include "Client.h"
#include <memory>
#include "BuildCard.h"
#include "CharacterCard.h"
#include <random>

using namespace std;

class Game
{

public:
	void initialise();
	void run() const;

	void divide_cards() const;
	const bool is_valid_id(const vector<shared_ptr<CharacterCard>> cards, int id) const;
	const int get_card_id (const vector<shared_ptr<CharacterCard>> &cards, int id) const;


private:
	vector<shared_ptr<BuildCard>> buildCards;
	vector<shared_ptr<CharacterCard>> characterCards;
	vector<shared_ptr<Client>> winners;
	

};

