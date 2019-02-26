#pragma once
#include <list>
#include <vector>
#include "GameObject.h"
#include "Camera.h"

class Game;

class GameState
{
	private:
		void initializeCamera();

	protected:
		list <GameObject*> _stages;
		Game* _gameptr;
		Camera* _mainCamera = nullptr;

	public:
		GameState(Game* g) : _gameptr(g) { initializeCamera(); }
		virtual ~GameState();
		virtual void render() const;
		virtual void update();
		virtual bool handleEvents(SDL_Event& e);

		virtual Camera* getMainCamera() { return _mainCamera; };
		virtual list <GameObject*> getObjects() { return _stages; }
};