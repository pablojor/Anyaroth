#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ButtonUI.h"
#include "ShopItem.h"

#include <list>

class Player;

class DepotPanel : public PanelUI
{
	private:
		Player* _player = nullptr;

		ImageUI* _depotFrame = nullptr;
		ImageUI* _equipmentFrame = nullptr;

		ButtonUI* _exitButton = nullptr;

		ShopItem* _firstWeapon = nullptr;
		ShopItem* _secondWeapon = nullptr;
		ShopItem* _meleeWeapon = nullptr;

		list<ShopItem*> _items;

		static ShopItem* _selectedItem;

	public:
		DepotPanel(Game* game, Player* player);

		static void selectDistanceWeapon(Game* game, ShopItem* item);
		static void setDistanceWeapon(Game* game);
		static void selectMeleeWeapon(Game* game);
		static void setMeleeWeapon(Game* game);
};

