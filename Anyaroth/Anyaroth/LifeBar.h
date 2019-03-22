#pragma once
#include "ImageUI.h"

class LifeBar : public ImageUI
{
	private:
		bool inUse;
	public:
		LifeBar(Game* game, string textName, int xPos = 0, int yPos = 0, bool inUse = true);
		~LifeBar() {}

		void updateLifeBar(const int& life, const int& maxLife);

		void setInUse(bool b) { inUse = b; }
};