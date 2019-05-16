#pragma once
#include "Canvas.h"
#include "CreditsPanel.h"


class Game;

class CreditsStateHUD :	public Canvas
{
private:
	CreditsPanel* _creditsPanel;
public:
	CreditsStateHUD(Game* game, bool goodFinal);
	~CreditsStateHUD();
};

