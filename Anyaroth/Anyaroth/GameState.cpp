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

void GameState::handleEvents(SDL_Event& e)
{
	for (GameObject* o : _stages)
		o->handleInput(e);
}

void GameState::initializeCamera()
{
	_mainCamera = new Camera();
	_mainCamera->setCameraSize(GAME_RESOLUTION_X, GAME_RESOLUTION_Y);
	_stages.push_back(_mainCamera);
}
