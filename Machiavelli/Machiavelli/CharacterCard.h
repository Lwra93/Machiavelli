#pragma once
#include <string>
#include <vector>
#include "Client.h"

using namespace std;

class Client;

class CharacterCard
{
public:
	CharacterCard(int id, string name) { this->id = id; this->name = name; this->robbed = false; };
	virtual void handle(shared_ptr<Client> current, shared_ptr<Client> opponent, vector<shared_ptr<CharacterCard>> list, vector<shared_ptr<BuildCard>> availableCards) {};

	const int get_id() const { return this->id; }
	const string get_name() const  { return this->name; };

	void reset();

	void kill();
	const bool isDead() const;

	void rob();
	const bool isRobbed() const;

protected:
	int id;
	std::string name;
	bool dead = false;
	bool robbed = false;

};
