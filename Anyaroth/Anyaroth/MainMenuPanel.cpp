#include "MainMenuPanel.h"
#include "Game.h"


MainMenuPanel::MainMenuPanel(Game* g)
{
	int buttonH = 20;
	int buttonW = 80;

	_playButton = new ButtonUI(g, g->getTexture("Play"), [this](Game* game) { startGame(game); });
	_playButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 50);
	_playButton->setSize(buttonW, buttonH);

	_optionsButton = new ButtonUI(g, g->getTexture("Coin"), [this](Game* game) { options(game); });
	_optionsButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 + buttonH + 50);
	_optionsButton->setSize(buttonW, buttonH);

	_exitButton = new ButtonUI(g, g->getTexture("Exit"), [this](Game* game) { exitGame(game); });
	_exitButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 + buttonH + 100);
	_exitButton->setSize(buttonW, buttonH);

	addChild(_playButton);
	addChild(_exitButton);
	addChild(_optionsButton);
}


MainMenuPanel::~MainMenuPanel()
{
}


void MainMenuPanel::startGame(Game * g)
{
	g->changeState(new PlayState(g));
}

void MainMenuPanel::options(Game * g)
{
	_visible = !_visible;
	g->getCurrentState()->getMenuHUD()->getOptionsPanel()->setVisible(true);
}

void MainMenuPanel::exitGame(Game * g)
{
	g->setExit(true);
}