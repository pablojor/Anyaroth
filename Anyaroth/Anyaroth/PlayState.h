#pragma once


#include "GameState.h"


class PlayState : public GameState
{
	private:
	public:
		PlayState(Game* g);

		virtual void update();
		virtual void handleEvents(SDL_Event& e);

};
