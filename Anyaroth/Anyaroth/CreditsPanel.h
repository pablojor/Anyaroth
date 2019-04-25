#pragma once
#include "PanelUI.h"
#include "TextUI.h"
#include "ButtonUI.h"
class CreditsPanel : public PanelUI
{
private:
	ButtonUI * _menuButton = nullptr;
	TextUI* _buttonText = nullptr;

	TextUI* _text = nullptr;

	void goToMenu(Game* game);
public:
	CreditsPanel(Game* g);
	virtual ~CreditsPanel();
};

