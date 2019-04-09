#pragma once
#include "Interactable.h"
#include "ShopMenu.h"

class Shop : public Interactable
{
	private:
		ShopMenu* _shop = nullptr;

		int _currentZone;

	public:
		Shop(Game* g, Vector2D posIni, ShopMenu* shop, int currentZone);

		virtual void interact();
};

