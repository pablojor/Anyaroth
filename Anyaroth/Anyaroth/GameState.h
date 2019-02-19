#pragma once

#include <list>
#include <vector>
#include "GameObject.h"
#include "Camera.h"

class Game;

class GameState
{
	protected:
		list <GameObject*> _stages;
		Game* _gameptr;
		Camera* _mainCamera = nullptr;

	public:
		GameState(Game* g) : _gameptr(g) {}
		virtual ~GameState();
		virtual void render() const;
		virtual void update();
		virtual void handleEvents(SDL_Event& e);

		virtual void initializeCamera() { _mainCamera = new Camera(); };
		virtual Camera* getMainCamera() { return _mainCamera; };
};