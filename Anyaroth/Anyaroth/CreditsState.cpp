#include "CreditsState.h"
#include "CreditsStateHUD.h"
#include "Game.h"

CreditsState::CreditsState(Game* game) : GameState(game)
{
	game->getSoundManager()->stopMusic();

	SDL_ShowCursor(true);
	setCanvas(new CreditsStateHUD(game));
	_mainCamera->fadeIn(1500);
}

CreditsState::~CreditsState()
{
}