#pragma once
#include "GameState.h"
#include "Game.h"
#include "MenuStateHUD.h"

class MenuState : public GameState
{
public:
	MenuState(Game* g);
	~MenuState() {}

	virtual void start();
};