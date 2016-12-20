#pragma once
#include <vector>
#include "Client.h"
#include <memory>
#include "BuildCard.h"
#include "CharacterCard.h"
#include <random>
#include <functional>

using namespace std;

class Game
{

public:
	void initialise();
	void run();

	void divide_cards();
	void call_characters(vector<shared_ptr<BuildCard>> &buildings);
	shared_ptr<Client> who_has_card(const shared_ptr<CharacterCard> card);
	const shared_ptr<CharacterCard> get_character_by_name(const std::string name) const;

	const bool is_valid_id(const vector<shared_ptr<CharacterCard>> cards, int id) const;
	const int get_card_id (const vector<shared_ptr<CharacterCard>> cards, int id) const;

	const int calculate_score(const shared_ptr<Client>) const;
	const int calculate_no_bonus(const shared_ptr<Client>) const;

	void print_buildings(const shared_ptr<Client> current) const;

	void play_first(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> buildings, bool& first, shared_ptr<Client> current) const;
	void play_second(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> buildings, bool& second, shared_ptr<Client> current);
	void play_feature(shared_ptr<CharacterCard> currentCard, vector<shared_ptr<BuildCard>> buildings, bool& feature, shared_ptr<Client> current) const;

private:
	vector<shared_ptr<BuildCard>> buildCards;
	vector<shared_ptr<CharacterCard>> characterCards;
	vector<shared_ptr<CharacterCard>> discardedCharacters;
	vector<shared_ptr<Client>> winners;
	

};

