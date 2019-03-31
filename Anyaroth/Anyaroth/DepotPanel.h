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

		ImageUI* _firstWeapon = nullptr;
		ImageUI* _secondWeapon = nullptr;
		ImageUI* _meleeWeapon = nullptr;

		list<ShopItem*> _items;
		ShopItem* _selectedItem = nullptr;

	public:
		DepotPanel(Game* game, Player* player);
};

