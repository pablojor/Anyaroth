#pragma once
#include "GameState.h"
#include "Game.h"
#include "MenuStateHUD.h"

class MenuState : public GameState
{
private:
	MenuStateHUD* _menuHUD;
	static void startGame(Game* g);
	static void exitGame(Game* g);

public:
	MenuState(Game* g);
	~MenuState() {}
};