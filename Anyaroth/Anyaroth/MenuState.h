#pragma once
#include "GameState.h"
#include "Game.h"
#include "MenuStateHUD.h"

class MenuState : public GameState
{
private:
	MenuStateHUD* _menuHUD;

public:
	MenuState(Game* g);
	~MenuState() {}
};