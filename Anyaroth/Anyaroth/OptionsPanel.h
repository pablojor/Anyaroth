#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"

class OptionsPanel : public PanelUI
{
private:
	ButtonUI *_moreVolume, *_lessVolume;



	ButtonUI* _backButton;

	bool _menu;
	int _volume;
public:
	OptionsPanel(Game* g, bool mainMenu);
	~OptionsPanel();

	void moreVolume(Game * g);
	void lessVolume(Game * g);

	void back(Game * g);
};
