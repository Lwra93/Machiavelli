#pragma once
#include "CharacterCard.h"
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include "BuildCard.h"

namespace factory
{

	void initialise();
	vector<string> split(const string&, char delim);
	shared_ptr<BuildCard> get_building(string name, int value, string color, string description);
	shared_ptr<CharacterCard> get_character(int id, string name);
	vector<shared_ptr<BuildCard>> load_buildings();
	vector<shared_ptr<CharacterCard>>load_characters();
	void add_card(int, string, vector<CharacterCard> &elems);

}
