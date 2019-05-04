#include "PauseState.h"
#include "MenuState.h"

PauseState::PauseState(Game* g) : GameState(g)
{
}

void PauseState::start()
{
	_gameptr->getSoundManager()->pauseMusic();

	//Show cursor
	SDL_ShowCursor(true);

	//HUD
	_pauseHud = new PauseStateHUD(_gameptr);
	setCanvas(_pauseHud);

	//Fondo
	_mainCamera->setBackGround(new BackGround(_gameptr->getTexture("BgPauseMenu"), _mainCamera));
}