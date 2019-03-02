#pragma once
#include "PanelUI.h"
#include "ImageUI.h"


class WeaponryViewer : public PanelUI
{
	private:
		ImageUI* _currentWeapon = nullptr;
		ImageUI* _otherWeapon = nullptr;
		ImageUI* _meleeWeapon = nullptr;

	public:
		WeaponryViewer(Game* game, int xPos, int yPos);
		~WeaponryViewer() {};
		
		void updateWeaponryViewer();

};

