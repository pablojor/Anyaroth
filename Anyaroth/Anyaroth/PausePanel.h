#pragma once
#include "PanelUI.h"
#include "ButtonUI.h"
#include "TextUI.h"

class PausePanel : public PanelUI
{
	private:
		ButtonUI * _playButton;
		ButtonUI * _optionsButton;
		ButtonUI * _menuButton;

		TextUI * _playText;
		TextUI * _optionsText;
		TextUI * _menuText;

	public:
		PausePanel(Game* g);
		~PausePanel();

		virtual bool handleEvent(const SDL_Event& event);
		void continueGame(Game * g);
		void options(Game * g);
		void returnMenu(Game * g);
};

