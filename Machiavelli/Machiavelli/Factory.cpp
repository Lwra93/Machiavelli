#pragma once
#include "Factory.h"
#include "Moordenaar.h"
#include "Dief.h"
#include "Magier.h"
#include "Koning.h"
#include "Prediker.h"
#include "Koopman.h"
#include "Bouwmeester.h"
#include "Condottiere.h"
#include <functional>
#include "BuildCard.h"
#include "PurpleCard.h"
#include "config.h"
#include "Kerker.h"
#include "Kerkhof.h"
#include "Hof.h"
#include "Laboratorium.h"
#include "Werkplaats.h"
#include "Observatorium.h"
#include "Bibliotheek.h"
#include "School.h"
#include "Drakenpoort.h"
#include "Universiteit.h"

namespace factory
{

	static map<string, function<shared_ptr<CharacterCard>(int, string)>> characterFactory;
	static map < string, function <shared_ptr<BuildCard>(string, int, string, string)>> buildingFactory;

	void initialise()
	{

		if(characterFactory.size() == 0)
		{
			characterFactory.emplace("Moordenaar", [](int id, string naam)-> shared_ptr<CharacterCard> { return make_shared<Moordenaar>(id, naam); });
			characterFactory.emplace("Dief", [](int id, string naam)-> shared_ptr<CharacterCard> { return make_shared<Dief>(id, naam); });
			characterFactory.emplace("Magiër", [](int id, string naam)-> shared_ptr<CharacterCard> { return make_shared<Magier>(id, naam); });
			characterFactory.emplace("Koning", [](int id, string naam)-> shared_ptr<CharacterCard> { return make_shared<Koning>(id, naam); });
			characterFactory.emplace("Prediker", [](int id, string naam)-> shared_ptr<CharacterCard> { return make_shared<Prediker>(id, naam); });
			characterFactory.emplace("Koopman", [](int id, string naam)-> shared_ptr<CharacterCard> { return make_shared<Koopman>(id, naam); });
			characterFactory.emplace("Bouwmeester", [](int id, string naam)-> shared_ptr<CharacterCard> { return make_shared<Bouwmeester>(id, naam); });
			characterFactory.emplace("Condottiere", [](int id, string naam)-> shared_ptr<CharacterCard> { return make_shared<Condottiere>(id, naam); });
		}
		
		if(buildingFactory.size() == 0)
		{
			buildingFactory.emplace("Hof der Wonderen", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Hof>(name, value, color, description); });
			buildingFactory.emplace("Kerker", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Kerker>(name, value, color, description); });
			buildingFactory.emplace("Kerkhof", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Kerkhof>(name, value, color, description); });
			buildingFactory.emplace("Laboratorium", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Laboratorium>(name, value, color, description); });
			buildingFactory.emplace("Werkplaats", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Werkplaats>(name, value, color, description); });
			buildingFactory.emplace("Observatorium", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Observatorium>(name, value, color, description); });
			buildingFactory.emplace("Bibliotheek", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Bibliotheek>(name, value, color, description); });
			buildingFactory.emplace("School", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<School>(name, value, color, description); });
			buildingFactory.emplace("Drakenpoort", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Drakenpoort>(name, value, color, description); });
			buildingFactory.emplace("Universiteit", [](string name, int value, string color, string description)-> shared_ptr<PurpleCard> { return make_shared<Universiteit>(name, value, color, description); });
			buildingFactory.emplace("Other", [](string name, int value, string color, string description)-> shared_ptr<BuildCard> { return make_shared<BuildCard>(name, value, color); });
		}
	}

	
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

	shared_ptr<BuildCard> get_building(string name, int value, string color, string description)
	{
		auto it = (buildingFactory.find(name) != buildingFactory.end() ? buildingFactory.find(name) : buildingFactory.find("Other"));
		return move(it->second(name, value, color, description));
	}

	shared_ptr<CharacterCard> get_character(int id, string name)
	{

		auto it = characterFactory.find(name);
		if(it != characterFactory.end())
			return move(it->second(id, name));

		return nullptr;
	}

	vector<shared_ptr<BuildCard>> load_buildings()
	{
		
		auto path = config::buildingCardsLocation;
		vector<shared_ptr<BuildCard>> buildings;
		ifstream file{ path };

		file >> buildings;

		return buildings;

	}

	vector<shared_ptr<CharacterCard>> load_characters()
	{

		auto path = config::characterCardsLocation;
		vector<shared_ptr<CharacterCard>> cards;
		ifstream file{ path };

		file >> cards;

		return cards;

	}

	std::ifstream& operator>>(std::ifstream& stream, vector<shared_ptr<BuildCard>>& vector)
	{

		std::string line;

		if (stream.is_open())
		{

			while (getline(stream, line))
			{

				auto values = factory::split(line, ';');
				auto name = values[0];
				auto value = stoi(values[1]);
				auto color = values[2];
				auto description = (values.size() > 3 ? values[3] : "");

				vector.push_back(move(factory::get_building(name, value, color, description)));


			}
		}

		return stream;

	}

	std::ifstream& operator>>(std::ifstream& stream, vector<shared_ptr<CharacterCard>>& vector)
	{

		std::string line;

		if (stream.is_open())
		{
			while (getline(stream, line))
			{

				auto values = split(line, ';');
				auto id = stoi(values[0]);
				auto name = values[1];

				vector.push_back(move(get_character(id, name)));


			}
		}

		return stream;

	}
}
