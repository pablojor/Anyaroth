#pragma once
#include "ImageUI.h"

class LifeBar : public ImageUI
{
	public:
		LifeBar(Game* game, Texture* texture, int xPos, int yPos);
		~LifeBar() {};

		void updateLifeBar(const int& life, const int& maxLife);
};