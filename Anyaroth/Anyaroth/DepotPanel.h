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
		static Player* _player;

		ImageUI* _depotFrame = nullptr;
		ImageUI* _equipmentFrame = nullptr;

		ButtonUI* _exitButton = nullptr;
		ButtonUI* _changeButton = nullptr;

		static ShopItem* _firstWeapon;
		static ShopItem* _secondWeapon;
		static ShopItem* _meleeWeapon;

		list<ShopItem*> _items;

		static ShopItem* _selectedItem;

	public:
		DepotPanel(Game* game);

		void setPlayer(Player* ply) { _player = ply; }

		static void changeEquipedGuns(Game* game);
		static void selectDistanceWeapon(Game* game, ShopItem* item);
		static void setDistanceWeapon(Game* game);
		static void selectMeleeWeapon(Game* game);
		static void setMeleeWeapon(Game* game);
};

