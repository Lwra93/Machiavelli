//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "CharacterCard.h"
#include "BuildCard.h"
#include <vector>
#include <string>
#include <memory>

class Player {
public:
	Player() {};
	Player(const std::string& name, const int age) : name{ name }, age{ age }, gold{ 2 } {}

    std::string get_name() const { return name; }
	int get_age() const { return age; }

	void flush();
	void add_character_card(const shared_ptr<CharacterCard> card);
	void add_building_card(const shared_ptr<BuildCard> card);
	void remove_building_card(const int id);
	void add_building(const shared_ptr<BuildCard> card);
	void remove_building(const int id);

	vector<shared_ptr<CharacterCard>> get_character_cards() const;
	vector<shared_ptr<BuildCard>> get_building_cards() const;
	vector<shared_ptr<BuildCard>> get_buildings() const;


	int get_gold() const;
	void add_gold(const int gold);

private:
    std::string name;
	int age;
	int gold;
	vector<shared_ptr<CharacterCard>> characterCards;
	vector<shared_ptr<BuildCard>> buildingCards;
	vector<shared_ptr<BuildCard>> built;

};

#endif /* Player_hpp */
