#include "MainMenuPanel.h"
#include "Game.h"


MainMenuPanel::MainMenuPanel(Game* g)
{
	int buttonH = 20;
	int buttonW = 80;

	_playButton = new ButtonUI(g, g->getTexture("Play"), [this](Game* game) { startGame(game); });
	_playButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 2 - buttonH + 50);
	_playButton->setSize(buttonW, buttonH);

	_exitButton = new ButtonUI(g, g->getTexture("Exit"), [this](Game* game) { exitGame(game); });
	_exitButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 2 + buttonH + 50);
	_exitButton->setSize(buttonW, buttonH);

	addChild(_playButton);
	addChild(_exitButton);
}


MainMenuPanel::~MainMenuPanel()
{
}


void MainMenuPanel::startGame(Game * g)
{
	g->changeState(new PlayState(g));
}

void MainMenuPanel::exitGame(Game * g)
{
	g->setExit(true);
}