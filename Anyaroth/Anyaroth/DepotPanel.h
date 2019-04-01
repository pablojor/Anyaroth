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

		ShopItem* _selectedItem = nullptr;

		int itemsPerRow = 2;
		int itemsPerCol = 4;
		int itemWidth;
		int itemHeight;
		int itemSize;

	public:
		DepotPanel(Game* game);
		virtual ~DepotPanel();

		void setPlayer(Player* ply) { _player = ply; }

		void changeEquipedGuns(Game* game);
		void selectDistanceWeapon(Game* game);
		void setDistanceWeapon(Game* game);
		void selectMeleeWeapon(Game* game);
		void setMeleeWeapon(Game* game);

		void setItems(list<ShopItem*>& list);
		void selectItem(Game * game, ShopItem* item);

		void reorderDepot();
};

