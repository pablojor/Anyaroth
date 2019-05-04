#include "MainMenuPanel.h"
#include "Game.h"


MainMenuPanel::MainMenuPanel(Game* g) : PanelUI(g)
{
	//----BOTONES----//

	_playButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { startGame(game); }, { 0, 1, 2, 2, 2 });
	int buttonW = _playButton->getW(),
		buttonH = _playButton->getH();
	_playButton->setPosition(CAMERA_RESOLUTION_X / 2 - 4/3*buttonW, CAMERA_RESOLUTION_Y - 93);
	_playButton->setSize(buttonW, buttonH);

	_loadButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game * game) { loadGame(game); }, { 0, 1, 2, 2, 2 }, 1);
	_loadButton->setPosition(CAMERA_RESOLUTION_X / 2 + buttonW/3, _playButton->getY());
	_loadButton->setSize(buttonW, buttonH);

	_optionsButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { options(game); }, { 0, 1, 2, 2, 2 }, 2);
	_optionsButton->setPosition(_playButton->getX() , _playButton->getY() + buttonH + 10);
	_optionsButton->setSize(buttonW, buttonH);

	_exitButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { exitGame(game); }, { 0, 1, 2, 2, 2 }, 3);
	_exitButton->setPosition(_loadButton->getX() , _optionsButton->getY());
	_exitButton->setSize(buttonW, buttonH);


	_playButton->setNextButtons({ _loadButton, _optionsButton, _loadButton, _optionsButton });
	_optionsButton->setNextButtons({ _exitButton, _playButton, _exitButton, _playButton });
	_loadButton->setNextButtons({ _playButton, _exitButton, _playButton, _exitButton });
	_exitButton->setNextButtons({ _optionsButton, _loadButton, _optionsButton, _loadButton });

	//----TEXTOS----//

	_playText = new TextUI(g, "Play", g->getFont("ARIAL12"), 12);
	_playText->setPosition(_playButton->getX() + buttonW / 2 - _playText->getW() / 2,
						   _playButton->getY() + buttonH / 2 - _playText->getH() / 2);

	_loadText = new TextUI(g, "Load", g->getFont("ARIAL12"), 12);
	_loadText->setPosition(_loadButton->getX() + buttonW / 2 - _loadText->getW() / 2,
		                   _loadButton->getY() + buttonH / 2 - _loadText->getH() / 2);

	_optionsText = new TextUI(g, "Options", g->getFont("ARIAL12"), 12);
	_optionsText->setPosition(_optionsButton->getX() + buttonW / 2 - _optionsText->getW() / 2,
							  _optionsButton->getY() + buttonH / 2 - _optionsText->getH() / 2);

	_exitText = new TextUI(g, "Exit", g->getFont("ARIAL12"), 12);
	_exitText->setPosition(_exitButton->getX() + buttonW / 2 - _exitText->getW() / 2,
						   _optionsText->getY());

	addChild(_playButton);
	addChild(_loadButton);
	addChild(_exitButton);
	addChild(_optionsButton);
	addChild(_playText);
	addChild(_loadText);
	addChild(_optionsText);
	addChild(_exitText);

	_selectedButton = _playButton;

	if (_game->usingJoystick())
	{
		_selectedButton->setSelected(true);
		SDL_ShowCursor(false);
		SDL_WarpMouseGlobal(0, 0);
	}
}

MainMenuPanel::~MainMenuPanel()
{
}

void MainMenuPanel::startGame(Game * g)
{
	g->changeState(new PlayState(g));
}

void MainMenuPanel::loadGame(Game* g)
{
	auto p = new PlayState(g);
	g->changeState(p);
	p->setLoaded(true);
	p->start();
	p->setStarted(true);
	p->loadGame();
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