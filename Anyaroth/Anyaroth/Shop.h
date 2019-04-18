#pragma once
#include "Interactable.h"
#include "ShopMenu.h"

class Shop : public Interactable
{
	private:
		ShopMenu* _shop = nullptr;

	public:
		Shop(Game* g, Vector2D posIni, ShopMenu* shop);

		virtual void interact();
};

