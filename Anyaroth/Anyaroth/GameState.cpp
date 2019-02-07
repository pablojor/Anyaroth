#include "GameState.h"
#include "Game.h"

GameState::GameState(Game* g) {
	_gameptr = g;
}

GameState::~GameState()
{
	for (GameObject* o : _stages)
		delete o;
}
void GameState::render() const
{
	for (GameObject* o : _stages)
		o->render();
}

void GameState::update()
{
	for (GameObject* o : _stages)
		o->update();
}

void GameState::handleEvents(SDL_Event& e)
{
	for (GameObject* o : _stages)
		o->handleEvents(e);
}