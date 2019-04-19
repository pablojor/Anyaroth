#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"

class OptionsPanel : public PanelUI
{
private:
	ButtonUI *_moreVolume, *_lessVolume;



	ButtonUI* _backButton;

	bool _menu;
public:
	OptionsPanel(Game* g, bool mainMenu);
	~OptionsPanel();

	void back(Game * g);
	void options(Game * g);
	void exitGame(Game * g);
};
