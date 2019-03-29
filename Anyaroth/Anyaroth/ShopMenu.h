#pragma once
#include "PanelUI.h"
#include "CatalogPanel.h"
#include "ButtonUI.h"
#include "DialoguePanel.h"
#include "ImageUI.h"
#include "DepotPanel.h"
#include "CoinsCounter.h"

class Player;

class ShopMenu : public PanelUI
{
	private:
		Player* _player = nullptr;
		ImageUI* _imageBG = nullptr;
		CoinsCounter* _playerMoney = nullptr;

		static ButtonUI * _shopButton;
		static ButtonUI* _talkButton;
		static ButtonUI* _depotButton;
		static ButtonUI* _exitButton;

		static DialoguePanel* _dialoguePanel;
		static CatalogPanel* _catalogPanel;
		static DepotPanel* _depotPanel;

	public:
		ShopMenu(Game* game);

		//virtual void handleEvent(const SDL_Event& event) {};
		void setPlayer(Player* ply);

		void openShop();
		void open();
		void closeShop();

		inline DialoguePanel* getDialoguePanel() const { return _dialoguePanel; }

		static void ableMainMenu(Game* game);
		static void disableMainMenu(Game* game);

		static void openCatalogPanel(Game* game);
		static void closeCatalogPanel(Game* game);

		static void startTalking(Game* game);
		static void stopTalking(Game* game);

		static void openDepotPanel(Game* game);
		static void closeDepotPanel(Game* game);

		static void exit(Game* game);
};

