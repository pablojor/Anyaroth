#pragma once
#include "Canvas.h"
#include "ShopPanel.h"
#include "ButtonUI.h"
#include "DialoguePanel.h"
#include "ImageUI.h"
//#include "DepotPanel.h"

class ShopCanvas :	public Canvas
{
	private:
		ImageUI* _imageBG = nullptr;
		static ButtonUI * _shopButton;
		static ButtonUI* _talkButton;
		static ButtonUI* _depotButton;
		static ButtonUI* _exitButton;
											;
		static DialoguePanel* _dialoguePanel;

		static ShopPanel* _shopPanel;
		//DepotPanel* _depotPanel = nullptr;

	public:
		ShopCanvas(Game* game);
		~ShopCanvas() {};

		//virtual void handleEvent(const SDL_Event& event) {};

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

