#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "TextUI.h"

class CoinsCounter : public PanelUI
{
private:
	ImageUI* _coinImage = nullptr;
	TextUI* _coinText = nullptr;

public:
	CoinsCounter(Game* game, int xPos, int yPos);
	~CoinsCounter() {}

	void updateCoinsCounter(int cant);
};