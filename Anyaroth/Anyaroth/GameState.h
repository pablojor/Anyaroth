#pragma once

#include <list>
#include <vector>

#include "GameObject.h"

class Game;

class GameState
{
	protected:
		list <GameObject*> _stages;
		Game* _gameptr;

	public:
		GameState() {}
		virtual ~GameState();
		GameState(Game* g);
		virtual void render() const;
		virtual void update();
		virtual void handleEvents(SDL_Event& e);
};

