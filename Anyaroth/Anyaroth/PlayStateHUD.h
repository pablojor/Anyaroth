#pragma once
#include "Canvas.h"
#include "Game.h"
#include "ImageUI.h"

class PlayStateHUD : public Canvas
{
	private:
		ImageUI _lifeBar;
	public:
		PlayStateHUD(Game* g);
		~PlayStateHUD();
};

