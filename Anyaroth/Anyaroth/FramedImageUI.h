#pragma once

#include "ImageUI.h"

class FramedImageUI : public ImageUI
{
private:
	int _frame = 0;
public:
	FramedImageUI(Game* game, Texture* image, int xPos = 0, int yPos = 0);
	~FramedImageUI();

	void render() const;

	inline void changeFrame(int frame) { _frame = frame; }
};

