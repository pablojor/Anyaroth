#include "CreditsState.h"
#include "CreditsStateHUD.h"
#include "Game.h"

CreditsState::CreditsState(Game* game) : GameState(game)
{
}

CreditsState::~CreditsState()
{
}

void CreditsState::start()
{
	_gameptr->getSoundManager()->stopMusic();

	SDL_ShowCursor(true);
	setCanvas(new CreditsStateHUD(_gameptr));
	_mainCamera->fadeIn(1500);
}