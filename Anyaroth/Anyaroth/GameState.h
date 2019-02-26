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
		GameState(Game* g) : _gameptr(g) {}
		virtual ~GameState();
		virtual void render() const;
		virtual void update();
		virtual bool handleEvents(SDL_Event& e);
};