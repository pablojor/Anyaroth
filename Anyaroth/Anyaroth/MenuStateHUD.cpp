#include "MenuStateHUD.h"


MenuStateHUD::MenuStateHUD(Game* g)
{
	_mainMenuPanel = new MainMenuPanel(g);
	_optionsPanel = new OptionsPanel(g, true);

	addUIElement(_mainMenuPanel);
	addUIElement(_optionsPanel);
}

