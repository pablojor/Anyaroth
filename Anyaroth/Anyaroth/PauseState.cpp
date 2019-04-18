#include "PauseState.h"
#include "MenuState.h"

PauseState::PauseState(Game* g) : GameState(g)
{
	//Show cursor
	SDL_ShowCursor(true);

	//HUD
	_pauseHUD = new PauseStateHUD(g);
	setCanvas(_pauseHUD);
}