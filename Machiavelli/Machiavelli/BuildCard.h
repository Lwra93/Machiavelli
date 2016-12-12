#pragma once
#include <string>

using namespace std;

class BuildCard
{
	
public:
	BuildCard(string name, int value, string color);

	const string get_name() const;
	const int get_value() const;
	const string get_color() const;

private:
	string name;
	int value;
	string color;

};