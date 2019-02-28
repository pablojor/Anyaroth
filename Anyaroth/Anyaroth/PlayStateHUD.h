#pragma once
#include "Canvas.h"
#include "Game.h"
#include "ImageUI.h"
#include "TextUI.h"

class PlayStateHUD : public Canvas
{
	private:
		ImageUI _lifeBar;
		TextUI _ammo;
	public:
		PlayStateHUD(Game* g);
		~PlayStateHUD();
};

