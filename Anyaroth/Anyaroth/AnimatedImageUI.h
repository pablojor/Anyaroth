#pragma once

#include "ImageUI.h"

class AnimatedImageUI : public ImageUI
{
private:
	int _frame = 0;
public:
	AnimatedImageUI(Game* game, Texture* image, int xPos = 0, int yPos = 0);
	~AnimatedImageUI();

	virtual void update(double time);
};


