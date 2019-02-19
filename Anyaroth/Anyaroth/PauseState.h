#pragma once
#include "GameState.h"
#include "MenuButton.h"

class PauseState : public GameState
{
	public:
		PauseState(Game* g);
		~PauseState();

		static void MainMenu(Game* g);
		static void Continue(Game* g);
};