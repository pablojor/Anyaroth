#pragma once
#include "ImageUI.h"

class LifeBar : public ImageUI
{
public:
	LifeBar(Game* game, int xPos = 0, int yPos = 0);
	~LifeBar() {}

	void updateLifeBar(const int& life, const int& maxLife);
};