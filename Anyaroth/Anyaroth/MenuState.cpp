#include "MenuState.h"



MenuState::MenuState(Game* g) : GameState(g) {
	
}

void MenuState::handleEvents(SDL_Event& e)
{
	GameState::handleEvents(e);
}

void MenuState::update()
{
	GameState::update();
}