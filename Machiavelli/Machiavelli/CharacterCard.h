#pragma once
#include <string>

using namespace std;

class CharacterCard
{
public:
	CharacterCard(int id, string name) { this->id = id; this->name = name; };
	virtual void handle();

	const int get_id() const { return this->id; }
	const string get_name() const  { return this->name; };

protected:
	int id;
	std::string name;

};
