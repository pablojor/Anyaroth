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
		o->render();
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