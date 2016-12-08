#pragma once
#include "Factory.h"
#include "Dief.h"
#include "Magier.h"
#include "Koning.h"
#include "Prediker.h"
#include "Koopman.h"
#include "Bouwmeester.h"
#include "Condottiere.h"

namespace factory
{
	
	vector<string> split(const string &s, char delim) 
	{
		vector<string> elems;
		stringstream ss;
		ss.str(s);
		string item;
		
		while (getline(ss, item, delim))
			elems.push_back(item);
		
		return elems;
	}

	vector<CharacterCard> get_characters(string path)
	{


		vector<CharacterCard> cards;

		ifstream file{ path };
		string line;

		if (file.is_open())
		{
			while (getline(file, line))
			{

				auto values = split(line, ';');
				auto id = stoi(values[0]);
				auto name = values[1];

				add_card(id, name, cards);
				
			}
		}

		return move(cards);

	}

	void add_card(int id, string name, vector<CharacterCard> &elems)
	{
		

		if(name == "Moordenaar")
		{
			Moordenaar m{ id, name };
			elems.push_back(move(m));
		}
		else if(name == "Dief")
		{
			Dief d{ id, name };
			elems.push_back(move(d));
		}
		else if(name == "Magier")
		{
			Magier m{ id, name };
			elems.push_back(move(m));
		}
		else if(name == "Koning")
		{
			Koning k{ id, name };
			elems.push_back(move(k));
		}
		else if(name == "Prediker")
		{
			Prediker p{ id, name };
			elems.push_back(move(p));
		}
		else if(name == "Koopman")
		{
			Koopman k{ id, name };
			elems.push_back(move(k));
		}
		else if(name == "Bouwmeester")
		{
			Bouwmeester b{ id, name };
			elems.push_back(move(b));
		}
		else
		{
			Condottiere c{ id, name };
			elems.push_back(move(c));
		}

	}

}
