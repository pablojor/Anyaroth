#pragma once
#include "GameState.h"
#include "MenuButton.h"

class PauseState : public GameState
{
private:
	static void Continue(Game* g);
	static void MainMenu(Game* g);

public:
	PauseState(Game* g);
	~PauseState() {}
};