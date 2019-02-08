#include "PauseState.h"

PauseState::PauseState(Game* g) : GameState(g) {

}

void PauseState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void PauseState::update()
{
	GameState::update();
}