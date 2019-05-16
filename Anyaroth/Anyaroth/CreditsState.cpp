#include "CreditsState.h"
#include "CreditsStateHUD.h"
#include "Game.h"

CreditsState::CreditsState(Game* game, bool goodFinal) : GameState(game) , _goodFinal(goodFinal)
{
}

CreditsState::~CreditsState()
{
}

void CreditsState::start()
{
	_gameptr->getSoundManager()->stopMusic();

	SDL_ShowCursor(true);
	setCanvas(new CreditsStateHUD(_gameptr, _goodFinal));
	_mainCamera->fadeIn(1500);
}