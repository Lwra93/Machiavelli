#pragma once
#include "CharacterCard.h"
#include "Moordenaar.h"
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

namespace factory
{

	vector<string> split(const string&, char delim);
	vector<CharacterCard> get_characters(string path);
	void add_card(int, string, vector<CharacterCard> &elems);

}
