#include "GameState.h"

GameState::~GameState()
{
	for (GameObject* o : stages)
		delete o;
}
void GameState::render() const
{
	for (GameObject* o : stages)
		o->render();
}

void GameState::update()
{
	for (GameObject* o : stages)
		o->update();
}

void GameState::handleEvents(SDL_Event& e)
{
	for (GameObject* o : stages)
		o->handleEvents(e);
}