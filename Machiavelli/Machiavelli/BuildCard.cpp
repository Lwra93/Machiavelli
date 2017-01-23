#pragma once
#include "BuildCard.h"
#include "Factory.h"

BuildCard::BuildCard(string name, int value, string color)
{

	this->name = name;
	this->value = value;
	this->color = color;

}

const string BuildCard::get_name() const
{
	return this->name;
}

const int BuildCard::get_value() const
{
	return this->value;
}

const string BuildCard::get_color() const
{
	return this->color;
}

std::ostream& operator<<(std::ostream& out, const shared_ptr<BuildCard> card)
{

	out << "Name: ";
	out << card->get_name() << std::endl;
	out << "Color: ";
	out << card->get_color() << std::endl;
	out << "Value: ";
	out << card->get_value() << std::endl;

	return out;

}
