#pragma once

#include "ImageUI.h"

class FramedImageUI : public ImageUI
{
protected:
	int _frame = 0;
public:
	FramedImageUI(Game* game, Texture* image, int xPos = 0, int yPos = 0);
	~FramedImageUI();

	virtual void render() const;

	inline void changeFrame(int frame) { _frame = frame; }
	inline const int getFrame() const { return _frame; }
};

