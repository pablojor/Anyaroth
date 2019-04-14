#pragma once
#include "PanelUI.h"
#include "ImageUI.h"

class WeaponryViewer : public PanelUI
{
	private:
		ImageUI* _marco = nullptr;

		ImageUI* _currentWeapon = nullptr;
		ImageUI* _otherWeapon = nullptr;

	public:
		WeaponryViewer(Game* game, int xPos, int yPos);
		~WeaponryViewer() { delete _otherWeapon; }

		void updateWeaponryViewer(Texture* iconTex);
};