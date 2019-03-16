#pragma once

#include <list>

#include "GameComponent.h"
#include "GunType_def.h"

struct objectShop
{
	GunType gun_;
	string gunName_;
	int price_;
	bool available_;
};

class Shop : public GameComponent
{
	private:
		list<objectShop> _stock;

	public:
		Shop();
		virtual ~Shop();

		void loadFromFile(ifstream& input);
};

