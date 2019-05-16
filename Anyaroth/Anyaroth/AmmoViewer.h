#pragma once
#include "PanelUI.h"
#include "TextUI.h"
#include "ImageUI.h"

class AmmoViewer : public PanelUI
{
	private:
		ImageUI* _ammoImage = nullptr;
		TextUI* _clipText = nullptr;
		TextUI* _magazineText = nullptr;

	public:
		AmmoViewer(Game* game, int xPos, int yPos);
		~AmmoViewer() {}

		void updateAmmoViewer(int ammoClip, int ammoMagazine);
};