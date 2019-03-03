#pragma once
#include "PanelUI.h"
#include "TextUI.h"


class AmmoViewer : public PanelUI
{
	private:
		TextUI * _clipText = nullptr;
		TextUI * _magazineText = nullptr;

	public:
		AmmoViewer(Game* game, int xPos, int yPos);
		~AmmoViewer() {};

		void updateAmmoViewer(const int& ammoClip, const int& ammoMagazine);

};

