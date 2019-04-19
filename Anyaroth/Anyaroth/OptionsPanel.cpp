#include "OptionsPanel.h"
#include "Game.h"


OptionsPanel::OptionsPanel(Game* g, bool mainMenu) : _menu(mainMenu)
{
	int buttonH = 20;
	int buttonW = 80;

	_moreVolume = new ButtonUI(g, g->getTexture("Play"), [this](Game* game) { moreVolume(game); });
	_moreVolume->setPosition(CAMERA_RESOLUTION_X / 2 + buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 50);
	_moreVolume->setSize(buttonW, buttonH);

	_lessVolume = new ButtonUI(g, g->getTexture("Coin"), [this](Game* game) { lessVolume(game); });
	_lessVolume->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 50);
	_lessVolume->setSize(buttonW, buttonH);

	_moreSFXVolume = new ButtonUI(g, g->getTexture("Play"), [this](Game* game) { moreSFXVolume(game); });
	_moreSFXVolume->setPosition(CAMERA_RESOLUTION_X / 2 + buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 100);
	_moreSFXVolume->setSize(buttonW, buttonH);

	_lessSFXVolume = new ButtonUI(g, g->getTexture("Coin"), [this](Game* game) { lessSFXVolume(game); });
	_lessSFXVolume->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 100);
	_lessSFXVolume->setSize(buttonW, buttonH);

	_moreBright = new ButtonUI(g, g->getTexture("Play"), [this](Game* game) { moreBright(game); });
	_moreBright->setPosition(CAMERA_RESOLUTION_X / 2 + buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 150);
	_moreBright->setSize(buttonW, buttonH);

	_lessBright = new ButtonUI(g, g->getTexture("Coin"), [this](Game* game) { lessBright(game); });
	_lessBright->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 150);
	_lessBright->setSize(buttonW, buttonH);

	_backButton = new ButtonUI(g, g->getTexture("Exit"), [this](Game* game) { back(game); });
	_backButton->setPosition(CAMERA_RESOLUTION_X / 2 + 150, CAMERA_RESOLUTION_Y / 3 + 150);
	_backButton->setSize(20, 20);

	_screenButton = new ButtonUI(g, g->getTexture("Exit"), [this](Game* game) { fullScreen(game); });
	_screenButton->setPosition(CAMERA_RESOLUTION_X / 2 - 150, CAMERA_RESOLUTION_Y / 3 + 150);
	_screenButton->setSize(20, 20);

	addChild(_moreVolume);
	addChild(_lessVolume);
	addChild(_moreSFXVolume);
	addChild(_lessSFXVolume);
	addChild(_moreBright);
	addChild(_lessBright);
	addChild(_backButton);
	addChild(_screenButton);

	_visible = false;
}


OptionsPanel::~OptionsPanel()
{
}

void OptionsPanel::moreVolume(Game * g)
{
	_volume = g->getSoundManager()->getMusicVolume() / 128.0;
	if (_volume + 0.1 > 1)
		_volume = 1;
	else
		_volume += 0.1;

	g->getSoundManager()->setMusicVolume(_volume);
}

void OptionsPanel::lessVolume(Game * g)
{
	_volume = g->getSoundManager()->getMusicVolume() / 128.0;
	if (_volume - 0.1 < 0)
		_volume = 0;
	else
		_volume -= 0.1;

	g->getSoundManager()->setMusicVolume(_volume);
}

void OptionsPanel::moreSFXVolume(Game * g)
{
	_sfxVolume = g->getSoundManager()->getGeneralVolume() / 128.0;
	if (_sfxVolume + 0.1 > 1)
		_sfxVolume = 1;
	else
		_sfxVolume += 0.1;

	g->getSoundManager()->setGeneralVolume(_sfxVolume);
}

void OptionsPanel::lessSFXVolume(Game * g)
{
	_sfxVolume = g->getSoundManager()->getGeneralVolume() / 128.0;
	if (_sfxVolume - 0.1 < 0)
		_sfxVolume = 0;
	else
		_sfxVolume -= 0.1;

	g->getSoundManager()->setGeneralVolume(_sfxVolume);
}

void OptionsPanel::moreBright(Game * g)
{
	float bright = SDL_GetWindowBrightness(g->getWindow());

	if (bright >= 1)
		bright = 1;
	else
		bright += 0.1;

	SDL_SetWindowBrightness(g->getWindow(), bright);
}

void OptionsPanel::lessBright(Game * g)
{
	float bright = SDL_GetWindowBrightness(g->getWindow());

	if (bright <= 0)
		bright = 0;
	else
		bright -= 0.1;

	SDL_SetWindowBrightness(g->getWindow(), bright);
}

void OptionsPanel::back(Game * g)
{
	_visible = !_visible;
	if(_menu)
		g->getCurrentState()->getMenuHUD()->getMainMenuPanel()->setVisible(true);
	else
		g->getCurrentState()->getPauseHUD()->getPausePanel()->setVisible(true);
}

void OptionsPanel::fullScreen(Game* g)
{
	bool IsFullscreen = SDL_GetWindowFlags(g->getWindow()) & SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (IsFullscreen)
	{
		SDL_SetWindowFullscreen(g->getWindow(), 0);
	}
	else
	{
		SDL_SetWindowFullscreen(g->getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}