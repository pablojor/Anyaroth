#include "MenuStateHUD.h"


MenuStateHUD::MenuStateHUD(Game* g)
{
	_mainMenuPanel = new MainMenuPanel(g);

	addUIElement(_mainMenuPanel);
}

