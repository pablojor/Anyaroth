#pragma once
#include "GameState.h"

class PauseState : public GameState
{
	public:

		PauseState(Game* g);
		virtual void update();
		virtual void handleEvents(SDL_Event& e);
};

