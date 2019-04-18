#pragma once
#include "Canvas.h"
#include "MainMenuPanel.h"

class Game;

class MenuStateHUD : public Canvas
{
	private:
		MainMenuPanel* _mainMenuPanel = nullptr;

	public:
		MenuStateHUD() {};
		MenuStateHUD(Game* g);
		virtual ~MenuStateHUD() {};

		inline MainMenuPanel* getMainMenuPanel() const { return _mainMenuPanel; }
};

