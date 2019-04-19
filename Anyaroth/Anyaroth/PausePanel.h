#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"

class PausePanel : public PanelUI
{
private:
	ButtonUI * _playButton;
	ButtonUI * _optionsButton;
	ButtonUI * _exitButton;
public:
	PausePanel(Game* g);
	~PausePanel();

	void continueGame(Game * g);
	void options(Game * g);
	void returnMenu(Game * g);
};

