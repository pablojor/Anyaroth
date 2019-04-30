#include "PauseState.h"
#include "MenuState.h"

PauseState::PauseState(Game* g) : GameState(g)
{
	g->getSoundManager()->pauseMusic();

	//Show cursor
	SDL_ShowCursor(true);

	//HUD
	_pauseHud = new PauseStateHUD(g);
	setCanvas(_pauseHud);

	//Fondo
	_mainCamera->setBackGround(new BackGround(g->getTexture("BgPauseMenu"), _mainCamera));
}