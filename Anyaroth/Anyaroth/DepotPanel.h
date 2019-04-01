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

		int itemsPerRow = 4, 
			itemsPerCol = 4, 
			distanceBetweenEquipmentSlots = 10;

		int itemWidth, itemHeight, itemEquipWidth, itemEquipHeight, itemSize;

	public:
		DepotPanel(Game* game);
		virtual ~DepotPanel();

		void setPlayer(Player* ply) { _player = ply; }

		void setItems(list<ShopItem*>& list);
		void reorderDepot();

		void changeEquipedGuns(Game* game);
		void selectItem(Game * game, ShopItem* item);
		void setDistanceWeapon(Game* game);
		void setMeleeWeapon(Game* game);
};

