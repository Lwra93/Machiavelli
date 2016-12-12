//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "Player.h"
using namespace std;

void Player::flush()
{
	characters.clear();
	buildings.clear();

}

vector<shared_ptr<CharacterCard>> Player::get_characters() const
{
	return this->characters;
}

void Player::add_character(const shared_ptr<CharacterCard> card)
{
	characters.push_back(move(card));
}

void Player::add_building(const shared_ptr<BuildCard> card)
{
	buildings.push_back(move(card));
}

