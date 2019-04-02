#pragma once
#include "PanelUI.h"
#include "CatalogPanel.h"
#include "ButtonUI.h"
#include "DialoguePanel.h"
#include "ImageUI.h"
#include "DepotPanel.h"

class Player;

class ShopMenu : public PanelUI
{
	private:
		static Player* _player;

		static ButtonUI * _shopButton;
		static ButtonUI* _talkButton;
		static ButtonUI* _depotButton;
		static ButtonUI* _exitButton;

		static DialoguePanel* _dialoguePanel;
		static CatalogPanel* _catalogPanel;
		static DepotPanel* _depotPanel;

		ImageUI* _imageBG = nullptr;

		list<ShopItem*> _items;

		static int _zona;

		void loadWeaponInfo();

	public:
		ShopMenu(Game* game);
		~ShopMenu();

		void setPlayer(Player* ply);

		void openShop(int zona);
		static void closeShop();

		inline DialoguePanel* getDialoguePanel() const { return _dialoguePanel; }

		static void ableMainMenu(Game* game);
		static void disableMainMenu(Game* game);

		void openCatalogPanel(Game* game);
		static void closeCatalogPanel(Game* game);

		void startTalking(Game* game);
		void stopTalking();

		void openDepotPanel(Game* game);
		static void closeDepotPanel(Game* game);

		void exit(Game* game);
};

