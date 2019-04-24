#pragma once
#include "Canvas.h"
#include "TextUI.h"
#include "ButtonUI.h"

class Game;

class CreditsStateHUD :	public Canvas
{
private:
	ButtonUI * _menuButton = nullptr;
	TextUI* _buttonText = nullptr;

	TextUI* _text = nullptr;

	void goToMenu(Game* game);

public:
	CreditsStateHUD(Game* game);
	~CreditsStateHUD();
};

