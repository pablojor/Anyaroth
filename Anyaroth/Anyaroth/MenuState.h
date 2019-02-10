#pragma once
#include "GameState.h"

class MenuState : public GameState
{
	public:
		MenuState(Game* g);
		virtual void handleEvents(SDL_Event& e);
		virtual void update();
};

