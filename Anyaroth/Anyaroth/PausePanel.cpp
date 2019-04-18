#include "PausePanel.h"
#include "Game.h"


PausePanel::PausePanel(Game* g)
{
	int buttonH = 20;
	int buttonW = 80;

	_playButton = new ButtonUI(g, g->getTexture("Continue"), [this](Game* game) { continueGame(game); });
	_playButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 2 - buttonH + 50);
	_playButton->setSize(buttonW, buttonH);

	_exitButton = new ButtonUI(g, g->getTexture("Menu"), [this](Game* game) { returnMenu(game); });
	_exitButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 2 + buttonH + 50);
	_exitButton->setSize(buttonW, buttonH);

	addChild(_playButton);
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

void PausePanel::returnMenu(Game * g)
{
	g->setTimestep(1 / 60.0);
	g->popState();
	g->changeState(new MenuState(g));
}