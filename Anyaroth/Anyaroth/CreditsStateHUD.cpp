#include "CreditsStateHUD.h"
#include "Game.h"
#include "Camera.h"


CreditsStateHUD::CreditsStateHUD(Game* game)
{
	_creditsPanel = new CreditsPanel(game);

	addUIElement(_creditsPanel);
}


CreditsStateHUD::~CreditsStateHUD()
{
}



