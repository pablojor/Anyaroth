#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ButtonUI.h"

class Player;
class ShopMenu;

class DepotPanel : public PanelUI
{
	private:
		Player* _player = nullptr;
		ImageUI* frame = nullptr;
		ButtonUI* _exitButton = nullptr;
		ShopMenu* _shop = nullptr;

	public:
		DepotPanel(Game* game, ShopMenu* shop, Player* ply);

		void openDepot();
		void closeDepot();
};

