#include "OptionsPanel.h"
#include "Game.h"


OptionsPanel::OptionsPanel(Game* g, bool mainMenu) : _menu(mainMenu)
{
	int buttonH = 20;
	int buttonW = 80;

	//_moreVolume = new ButtonUI(g, g->getTexture("Play"));
	//_moreVolume->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 50);
	//_moreVolume->setSize(buttonW, buttonH);

	//_lessVolume = new ButtonUI(g, g->getTexture("Coin"));
	//_lessVolume->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 + buttonH + 50);
	//_lessVolume->setSize(buttonW, buttonH);

	_backButton = new ButtonUI(g, g->getTexture("Exit"), [this](Game* game) { back(game); });
	_backButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 + buttonH + 100);
	_backButton->setSize(buttonW, buttonH);

	//addChild(_moreVolume);
	//addChild(_lessVolume);
	addChild(_backButton);
}


OptionsPanel::~OptionsPanel()
{
}

void OptionsPanel::back(Game * g)
{
	_visible = !_visible;
	if(_menu)
		g->getCurrentState()->getMenuHUD()->getMainMenuPanel()->setVisible(true);
	else
		g->getCurrentState()->getPauseHUD()->getPausePanel()->setVisible(true);
}