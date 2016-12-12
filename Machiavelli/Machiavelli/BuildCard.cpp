#pragma once
#include "BuildCard.h"

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


