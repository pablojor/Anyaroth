#pragma once
#include "PanelUI.h"
#include "CatalogPanel.h"
#include "ButtonUI.h"
#include "DialoguePanel.h"
#include "ImageUI.h"
#include "DepotPanel.h"
#include "AnimatedImageUI.h"

class Player;

class ShopMenu : public PanelUI
{
	private:
		Player* _player;

		TextUI* _shopText;
		ButtonUI * _shopButton;
		TextUI* _talkText;
		ButtonUI* _talkButton;
		TextUI* _depotText;
		ButtonUI* _depotButton;
		ButtonUI* _exitButton;

		DialoguePanel* _dialoguePanel;
		CatalogPanel* _catalogPanel;
		DepotPanel* _depotPanel;

		AnimatedImageUI* _imageBG = nullptr;

		list<ShopItem*> _items;

		int _zone = 1;

		bool _talking = false;

		void loadWeaponInfo();

	public:
		ShopMenu(Game* game);
		~ShopMenu();

		virtual void update(const double& deltaTime);

		void setPlayer(Player* ply);

		void openShop(int zona);
		void closeShop();

		void setDialoguePanel(DialoguePanel* dialoguePanel);
		inline DialoguePanel* getDialoguePanel() const { return _dialoguePanel; }

		void ableMainMenu(Game* game);
		void disableMainMenu(Game* game);

		void openCatalogPanel(Game* game);
		void closeCatalogPanel(Game* game);

		void startTalking(Game* game);
		void stopTalking();

		void openDepotPanel(Game* game);
		void closeDepotPanel(Game* game);

		void exit(Game* game);
};

