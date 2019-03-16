#include "Shop.h"

Shop::Shop()
{
}


Shop::~Shop()
{
}

void Shop::loadFromFile(ifstream& input)
{
	bool reading = true;
	while (reading)
	{
		string s;
		input >> s;

		if (s == "*") reading = false;
		else
		{

		}
	}
}