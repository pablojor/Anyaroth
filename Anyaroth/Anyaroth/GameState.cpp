#include "GameState.h"
#include "Game.h"

GameState::~GameState()
{
	for (GameObject* o : _stages)
		delete o;
}
void GameState::render() const
{
	for (GameObject* o : _stages)
		o->render(_mainCamera);
}

void GameState::update()
{
	for (GameObject* o : _stages)
		o->update();
}

bool GameState::handleEvents(SDL_Event& e)
{
	bool handled = false;
	auto it = _stages.begin();

	while (!handled && it != _stages.end()) {
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
	_stages.push_back(_mainCamera);
}