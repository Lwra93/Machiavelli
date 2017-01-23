#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <functional>

using namespace std;

class BuildCard
{
	
public:
	BuildCard(string name, int value, string color);

	const string get_name() const;
	const int get_value() const;
	const string get_color() const;

	friend std::ostream& operator<<(std::ostream&, const shared_ptr<BuildCard>);

private:
	string name;
	int value;
	string color;

};