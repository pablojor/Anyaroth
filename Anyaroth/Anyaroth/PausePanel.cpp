#include "PausePanel.h"
#include "Game.h"


PausePanel::PausePanel(Game* g)
{
	int buttonH = 20;
	int buttonW = 80;

	_playButton = new ButtonUI(g, g->getTexture("Play"), [this](Game* game) { continueGame(game); });
	_playButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 50);
	_playButton->setSize(buttonW, buttonH);

	_optionsButton = new ButtonUI(g, g->getTexture("Coin"), [this](Game* game) { options(game); });
	_optionsButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 + buttonH + 50);
	_optionsButton->setSize(buttonW, buttonH);

	_exitButton = new ButtonUI(g, g->getTexture("Exit"), [this](Game* game) { returnMenu(game); });
	_exitButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 + buttonH + 100);
	_exitButton->setSize(buttonW, buttonH);

	addChild(_playButton);
	addChild(_optionsButton);
	addChild(_exitButton);
}


PausePanel::~PausePanel()
{
}


void PausePanel::continueGame(Game * g)
{
	g->setTimestep(1 / 60.0);
	g->popState();
}

void PausePanel::options(Game * g)
{
	_visible = !_visible;
	g->getCurrentState()->getPauseHUD()->getOptionsPanel()->setVisible(true);
}

void PausePanel::returnMenu(Game * g)
{
	g->setTimestep(1 / 60.0);
	g->popState();
	g->changeState(new MenuState(g));
}