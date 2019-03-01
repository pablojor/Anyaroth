#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "TextUI.h"

class CoinsCounter : public PanelUI
{
private:
	int _coinCount = 0;
	ImageUI* _coinImage = nullptr;
	TextUI* _coinText = nullptr;
public:
	CoinsCounter(Game* game, int xPos, int yPos);
	~CoinsCounter() {};

	void update();

	void updateCounter(int cant) { _coinCount = cant; }

	void updateAspect();
};

