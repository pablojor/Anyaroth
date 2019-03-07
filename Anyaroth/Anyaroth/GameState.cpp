#include "GameState.h"
#include "Game.h"

GameState::~GameState()
{
	delete _mainCamera;

	if (_canvas != nullptr)
		delete _canvas;

	for (GameObject* o : _stages)
		delete o;
}

void GameState::render() const
{
	_mainCamera->render();

	for (GameObject* o : _stages)
		o->render(_mainCamera);

	if(_canvas != nullptr)
		_canvas->render();
}

void GameState::update()
{
	_mainCamera->update();

	for (GameObject* o : _stages)
		o->update(); // Carlos says: si no le pasáis un único delta, gatitos morirán.

	if (_canvas != nullptr)
		_canvas->update();
}

bool GameState::handleEvents(SDL_Event& e)
{
	bool handled = false;
	auto it = _stages.begin();

	while (!handled && it != _stages.end())
	{
		if ((*it)->handleInput(e))
			handled = true;
		else
			it++;
	}
	return handled;
}

void GameState::initializeCamera()
{
	_mainCamera = new Camera();
	_mainCamera->setCameraPosition(0, 0);
	_mainCamera->setCameraSize(GAME_RESOLUTION_X, GAME_RESOLUTION_Y);
}