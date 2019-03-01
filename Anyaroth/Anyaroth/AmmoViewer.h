#pragma once
#include "PanelUI.h"
#include "TextUI.h"

class AmmoViewer : public PanelUI
{
private:
	TextUI * _clipText = nullptr;
	TextUI * _magazineText = nullptr;

	int ammoClip = 0, ammoMagazine = 0;

public:
	AmmoViewer(Game* game, int xPos, int yPos);
	~AmmoViewer() {};

	void updateAspect();
};

