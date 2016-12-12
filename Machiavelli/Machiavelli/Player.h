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
	Player(const std::string& name, const int age) : name{ name }, age{ age } {}

    std::string get_name() const { return name; }
	int get_age() const { return age; }

	void flush();
	void add_character(const shared_ptr<CharacterCard> card);
	void add_building(const shared_ptr<BuildCard> card);

	vector<shared_ptr<CharacterCard>> get_characters() const;

private:
    std::string name;
	int age;
	vector<shared_ptr<CharacterCard>> characters;
	vector<shared_ptr<BuildCard>> buildings;
};

#endif /* Player_hpp */
