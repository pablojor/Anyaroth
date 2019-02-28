#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "TextUI.h"
//#include "CoinCounterPanel"

class PlayerPanel :	public PanelUI
{
private:
	ImageUI* _lifeBar;
	TextUI* _ammoViewer;
	/*_gunSelector;
	_dashViever;
	_coinCounter;
*/

public:
	PlayerPanel() {};
	PlayerPanel(Game* game);
	~PlayerPanel();
};

