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
	characterCards.clear();
}

vector<shared_ptr<CharacterCard>> Player::get_character_cards() const
{
	return this->characterCards;
}

vector<shared_ptr<BuildCard>> Player::get_building_cards() const
{
	return this->buildingCards;
}

void Player::set_building_cards(const vector<shared_ptr<BuildCard>> cards)
{
	this->buildingCards = cards;
}

vector<shared_ptr<BuildCard>> Player::get_buildings() const
{
	return this->built;
}

int Player::get_gold() const
{
	return this->gold;
}

void Player::add_gold(const int gold)
{
	this->gold += gold;
}

const int Player::isKing() const
{
	return this->king;
}

void Player::add_character_card(const shared_ptr<CharacterCard> card)
{
	characterCards.push_back(move(card));
}

void Player::setKing(const int king)
{
	this->king = king;
}

void Player::add_building_card(const shared_ptr<BuildCard> card)
{
	buildingCards.push_back(move(card));
}

void Player::add_building(const shared_ptr<BuildCard> card)
{
	built.push_back(move(card));
}

void Player::remove_building_card(const int id)
{

	buildingCards.erase(buildingCards.begin() + id);

}

void Player::remove_building(const int id)
{
	built.erase(built.begin() + id);
}

