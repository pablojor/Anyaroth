#pragma once
#include "PanelUI.h"
#include "LifeBar.h"
#include "TextUI.h"
#include "CoinsCounter.h"
#include "AmmoViewer.h"

class PlayerPanel :	public PanelUI
{
private:
	LifeBar* _lifeBar;
	AmmoViewer* _ammoViewer;
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

	void update()
	{
		LIFE -= 3; if (LIFE < 0) LIFE = 0;
		MAX_LIFE--; if (MAX_LIFE < 0) MAX_LIFE = 0;

		_lifeBar->updateLifeBar(LIFE, MAX_LIFE);
		_ammoViewer->updateAmmoViewer(LIFE, MAX_LIFE);
		_coinsCounter->updateCoinsCounter(LIFE + MAX_LIFE);
	}
};

