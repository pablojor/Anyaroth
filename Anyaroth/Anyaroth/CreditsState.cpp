#include "CreditsState.h"
#include "CreditsStateHUD.h"


CreditsState::CreditsState(Game* game) : GameState(game)
{
	SDL_ShowCursor(true);
	setCanvas(new CreditsStateHUD(game));

	_mainCamera->fadeIn(1500);
}


CreditsState::~CreditsState()
{
}
