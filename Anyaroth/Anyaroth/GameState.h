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
	Game* _gameptr = nullptr;
	Camera* _mainCamera = nullptr;
	Canvas* _canvas = nullptr;

public:
	GameState(Game* g) : _gameptr(g) { initializeCamera(); }
	virtual ~GameState();

	virtual void render() const;
	virtual void update();
	virtual bool handleEvents(SDL_Event& e);

	inline virtual Camera* getMainCamera() const { return _mainCamera; }
	inline virtual list <GameObject*> getObjects() const { return _stages; }
	inline virtual void setCanvas(Canvas* canvas) { _canvas = canvas; }
};