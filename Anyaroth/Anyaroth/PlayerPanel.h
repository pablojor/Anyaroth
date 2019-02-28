#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"
#include "CoinsCounter.h"

class PlayerPanel :	public PanelUI
{
private:
	LifeBar* _lifeBar;
	TextUI* _ammoViewer;
	CoinsCounter* _coinsCounter;

	//Temporal
	int MAX_LIFE = 500;
	int LIFE = 500;
	/*_gunSelector;
	_dashViever;
*/

public:
	PlayerPanel() {};
	PlayerPanel(Game* game);
	~PlayerPanel();
};

