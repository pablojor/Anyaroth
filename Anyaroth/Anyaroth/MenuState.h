#pragma once
#include "GameState.h"
#include "Game.h"

class MenuState : public GameState
{
private:
	static void startGame(Game* g);
	static void exitGame(Game* g);

public:
	MenuState(Game* g);
	~MenuState() {}
};