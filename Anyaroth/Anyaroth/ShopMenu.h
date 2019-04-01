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

		int _zona = NULL;

		void loadWeaponInfo();

	public:
		ShopMenu(Game* game);
		~ShopMenu();

		//virtual void handleEvent(const SDL_Event& event) {};

		void setPlayer(Player* ply);

		void openShop(int zona);
		static void closeShop();

		inline DialoguePanel* getDialoguePanel() const { return _dialoguePanel; }

		static void ableMainMenu(Game* game);
		static void disableMainMenu(Game* game);

		static void openCatalogPanel(Game* game);
		static void closeCatalogPanel(Game* game);

		static void startTalking(Game* game);
		void stopTalking();

		static void openDepotPanel(Game* game);
		static void closeDepotPanel(Game* game);

		static void exit(Game* game);
};

