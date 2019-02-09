#pragma once
#include "GameState.h"
class MenuState :
	public GameState
{
public:
	
	MenuState(Game* g);
	virtual void update();
	virtual void handleEvents(SDL_Event& e);
};

