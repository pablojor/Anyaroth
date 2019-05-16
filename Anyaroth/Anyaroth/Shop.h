#pragma once
#include "Interactable.h"
#include "ShopMenu.h"
#include "SpriteObject.h"

class Shop : public Interactable
{
	private:
		SpriteObject* _shopDoor = nullptr;
		AnimatedSpriteComponent * _shopDoorAnim = nullptr;
		ShopMenu* _shop = nullptr;

		bool goIn = false;

	public:
		Shop(Game* g, Vector2D posIni, ShopMenu* shop);
		virtual ~Shop() {};

		virtual void update(double deltaTime);

		virtual bool interact();
};

