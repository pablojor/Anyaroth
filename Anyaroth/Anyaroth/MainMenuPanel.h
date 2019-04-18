#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"

class MainMenuPanel : public PanelUI
{
	private:
		ButtonUI * _playButton;
		ButtonUI * _optionsButton;
		ButtonUI * _exitButton;
	public:
		MainMenuPanel(Game* g);
		~MainMenuPanel();

		void startGame(Game * g);
		void options(Game * g);
		void exitGame(Game * g);
};

