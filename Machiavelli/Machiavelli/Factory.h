#pragma once
#include "CharacterCard.h"
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

namespace factory
{

	vector<string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		std::stringstream ss;
		ss.str(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}
	
	map<int, CharacterCard> get_characters(string path)
	{
		
		map<int, CharacterCard> map;

		ifstream file{ path };
		string line;

		if(file.is_open())
		{
			while(getline(file, line))
			{
			
				auto values = split(line, ';');
				auto id = stoi(values[0]);
				CharacterCard card{ id, values[1] };
				
				map.try_emplace(move(id), move(card));

			}
		}

		return map;

	}

	


}
