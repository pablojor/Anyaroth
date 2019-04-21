#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "ShopItem.h"
#include "ButtonUI.h"
#include "ShopInfoPanel.h"
#include "CoinsCounter.h"

#include <list>

class Player;
class ShopMenu;

class CatalogPanel : public PanelUI
{
	private:
		Player* _player;
		TextUI* _buyText;
		ButtonUI* _buyButton;
		ShopInfoPanel* _infoPanel;

		ImageUI* _frame = nullptr;
		ButtonUI* _exitButton = nullptr;

		list<ShopItem*>* _items;

		ShopItem* _selectedItem = nullptr;
		ImageUI* _itemIndicator = nullptr;
		CoinsCounter* _playerMoney = nullptr;

		int itemsPerRow = 2;
		int itemsPerCol = 4;

		int _zone = -1;

		void reorderCatalog();
		void showItemInfo(ShopItem* item);
		void showSelectedItemInfo();

	public:
		CatalogPanel(Game* game);
		~CatalogPanel() {};

		virtual bool handleEvent(const SDL_Event& event);

		void inicializeCallbacks(ShopMenu* menu);

		void setPlayer(Player* ply);

		void setItems(list<ShopItem*>* list);
		void removeItems();

		void openCatalog();
		void closeCatalog();

		void selectItem(Game* game, ShopItem* item);
		void buyItem(Game* game);
};

