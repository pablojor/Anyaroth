#pragma once
#include "PanelUI.h"
#include "ShopPanel.h"
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
		static ShopPanel* _shopPanel;
		static DepotPanel* _depotPanel;

	public:
		ShopMenu(Game* game);
		~ShopMenu() {};

		//virtual void handleEvent(const SDL_Event& event) {};
		inline void setPlayer(Player* ply) { _player = ply; }

		void openShop();
		void open();
		void closeShop();

		static void ableMainMenu(Game* game);
		static void disableMainMenu(Game* game);
		static void openShopPanel(Game* game);
		static void closeShopPanel(Game* game);
		static void startTalking(Game* game);
		static void stopTalking(Game* game);
		static void openDepotPanel(Game* game);
		static void closeDepotPanel(Game* game);
		static void exit(Game* game);
};

