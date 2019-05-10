#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ButtonUI.h"
#include "ShopItem.h"

#include <list>

class Player;
class ShopMenu;

class DepotPanel : public PanelUI
{
	private:
		Player* _player;

		ImageUI* _depotFrame = nullptr;
		ImageUI* _depotMeleeFrame = nullptr;
		ImageUI* _equipmentFrame = nullptr;

		FramedImageUI* _depotFrameName = nullptr;
		FramedImageUI* _equipmentFrameName = nullptr;

		TextUI* _depotName;
		TextUI* _equipName;

		ButtonUI* _exitButton = nullptr;
		ButtonUI* _changeButton = nullptr;

		ShopItem* _firstWeaponFrame;
		ShopItem* _secondWeaponFrame;
		ShopItem* _meleeWeaponFrame;

		ShopItem* _firstWeaponItem;
		ShopItem* _secondWeaponItem;
		ShopItem* _meleeWeaponItem;

		ShopItem* _voidItem;

		list<ShopItem*>* _weaponItems;
		list<ShopItem*>* _meleeItems;

		ShopItem* _selectedItem = nullptr;

		int itemsPerRow = 4, 
			itemsPerCol = 4, 
			distanceBetweenEquipmentSlots = 10;

		void checkPlayer();

	public:
		DepotPanel(Game* game);
		virtual ~DepotPanel() { delete _voidItem; };

		virtual bool handleEvent(const SDL_Event& event);

		void inicializeCallback(ShopMenu* menu);

		void setPlayer(Player* ply);

		void setWeaponItems(list<ShopItem*>* list);
		void removeWeaponItems();

		void setMeleeItems(list<ShopItem*>* list);
		void removeMeleeItems();

		void openDepotPanel();
		void closeDepotPanel();
		void reorderDepot();

		void changeEquipedGuns(Game* game);
		void selectItem(Game* game, ShopItem* item);
		void setDistanceWeapon(Game* game, ShopItem* item);
		void setMeleeWeapon(Game* game, ShopItem* item);

		void swapDistanceItems(ShopItem* other);
		void swapMeleeItems(ShopItem* other);
};

