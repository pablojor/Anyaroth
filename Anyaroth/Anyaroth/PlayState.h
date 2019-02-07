#pragma once

#include "GameState.h"
#include "ExampleObject.h"
#include "ExampleObject2.h"

class PlayState : public GameState
{
	private:
		ExampleObject* _ex = nullptr;
		ExampleObject2* _ex2 = nullptr;
	public:
		PlayState(Game* g);

		virtual void update();
		virtual void handleEvents(SDL_Event& e);

};
