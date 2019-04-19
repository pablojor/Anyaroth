#pragma once
#include "Canvas.h"
#include "MainMenuPanel.h"
#include "OptionsPanel.h"

class Game;

class MenuStateHUD : public Canvas
{
	private:
		MainMenuPanel* _mainMenuPanel = nullptr;
		OptionsPanel* _optionsPanel = nullptr;

	public:
		MenuStateHUD() {};
		MenuStateHUD(Game* g);
		virtual ~MenuStateHUD() {};

		inline MainMenuPanel* getMainMenuPanel() const { return _mainMenuPanel; }
		inline OptionsPanel* getOptionsPanel() const { return _optionsPanel; }
};

