#include "CreditsStateHUD.h"
#include "Game.h"
#include "Camera.h"


CreditsStateHUD::CreditsStateHUD(Game* game, bool goodFinal)
{
	_creditsPanel = new CreditsPanel(game, goodFinal);

	addUIElement(_creditsPanel);
}


CreditsStateHUD::~CreditsStateHUD()
{
}



