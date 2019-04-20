#include "MainMenuPanel.h"
#include "Game.h"


MainMenuPanel::MainMenuPanel(Game* g)
{
	//----BOTONES----//

	_playButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { startGame(game); }, { 0, 1, 2, 2, 2 });
	int buttonW = _playButton->getW(),
		buttonH = _playButton->getH();
	_playButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y - 93);
	_playButton->setSize(buttonW, buttonH);

	_optionsButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { options(game); }, { 0, 1, 2, 2, 2 });
	_optionsButton->setPosition(_playButton->getX() - buttonW, _playButton->getY() + buttonH + 10);
	_optionsButton->setSize(buttonW, buttonH);

	_exitButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { exitGame(game); }, { 0, 1, 2, 2, 2 });
	_exitButton->setPosition(_playButton->getX() + buttonW, _optionsButton->getY());
	_exitButton->setSize(buttonW, buttonH);

	_buttons.push_back(_playButton);
	_buttons.push_back(_optionsButton);
	_buttons.push_back(_exitButton);
	//----TEXTOS----//

	_playText = new TextUI(g, "Play", g->getFont("ARIAL12"), 12);
	_playText->setPosition(CAMERA_RESOLUTION_X / 2 - _playText->getW() / 2,
							_playButton->getY() + buttonH / 2 - _playText->getH() / 2);

	_optionsText = new TextUI(g, "Options", g->getFont("ARIAL12"), 12);
	_optionsText->setPosition(_optionsButton->getX() + buttonW / 2 - _optionsText->getW() / 2,
								_optionsButton->getY() + buttonH / 2 - _optionsText->getH() / 2);

	_exitText = new TextUI(g, "Exit", g->getFont("ARIAL12"), 12);
	_exitText->setPosition(_exitButton->getX() + buttonW / 2 - _exitText->getW() / 2,
							_optionsText->getY());

	addChild(_playButton);
	addChild(_exitButton);
	addChild(_optionsButton);
	addChild(_playText);
	addChild(_optionsText);
	addChild(_exitText);

	_buttons[_selectedButton]->setSelected(true);
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
	g->getCurrentState()->getMainCamera()->setBackGround(new BackGround(g->getTexture("BgOptionsMenu"), g->getCurrentState()->getMainCamera()));
	g->getCurrentState()->getMenuHUD()->getOptionsPanel()->setVisible(true);
}

void MainMenuPanel::exitGame(Game * g)
{
	g->setExit(true);
}