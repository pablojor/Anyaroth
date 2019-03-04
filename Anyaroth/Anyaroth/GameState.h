#pragma once

#include <list>
#include <vector>
#include "GameObject.h"
#include "Camera.h"
#include "Canvas.h"

class Game;

class GameState
{
	private:
		void initializeCamera();

	protected:
		list <GameObject*> _stages;
		Game* _gameptr;
		Camera* _mainCamera = nullptr;
		Canvas* _canvas = nullptr;

	public:
		GameState(Game* g) : _gameptr(g) { initializeCamera(); }
		virtual ~GameState();
		virtual void render() const;
		virtual void update();
		virtual void handleEvents(SDL_Event& e);

		virtual Camera* getMainCamera() { return _mainCamera; };
		virtual list <GameObject*> getObjects() { return _stages; }
		virtual void setCanvas(Canvas* canvas) { _canvas = canvas; }
};