#include "OptionsPanel.h"
#include "Game.h"


OptionsPanel::OptionsPanel(Game* g, bool mainMenu) : _menu(mainMenu), PanelUI(g)
{
	//----BOTONES----//

	//Cambiar valores
		//Volumen
	_moreVolume = new ButtonUI(g, g->getTexture("MenuPlusButton"), [this](Game* game) { moreVolume(game); }, { 0, 1, 2, 2, 2 }, 1);
	buttonW = _moreVolume->getW();
	buttonH = _moreVolume->getH();
	_moreVolume->setPosition(CAMERA_RESOLUTION_X / 2 + buttonW, CAMERA_RESOLUTION_Y - 212);

	_lessVolume = new ButtonUI(g, g->getTexture("MenuLessButton"), [this](Game* game) { lessVolume(game); }, { 0, 1, 2, 2, 2 }, 0);
	_lessVolume->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW * 2, CAMERA_RESOLUTION_Y - 212);
		
		//Efectos
	_moreSFXVolume = new ButtonUI(g, g->getTexture("MenuPlusButton"), [this](Game* game) { moreSFXVolume(game); }, { 0, 1, 2, 2, 2 }, 3);
	_moreSFXVolume->setPosition(_moreVolume->getX(), CAMERA_RESOLUTION_Y - 137);

	_lessSFXVolume = new ButtonUI(g, g->getTexture("MenuLessButton"), [this](Game* game) { lessSFXVolume(game); }, { 0, 1, 2, 2, 2 }, 2);
	_lessSFXVolume->setPosition(_lessVolume->getX(), CAMERA_RESOLUTION_Y - 137);
	
		//Brillo
	_moreBright = new ButtonUI(g, g->getTexture("MenuPlusButton"), [this](Game* game) { moreBright(game); }, { 0, 1, 2, 2, 2 }, 5);
	_moreBright->setPosition(CAMERA_RESOLUTION_X / 2 + buttonW / 4, CAMERA_RESOLUTION_Y - 61);

	_lessBright = new ButtonUI(g, g->getTexture("MenuLessButton"), [this](Game* game) { lessBright(game); }, { 0, 1, 2, 2, 2 }, 4);
	_lessBright->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 4 - buttonW, CAMERA_RESOLUTION_Y - 61);

	//Volver menu
	_backButton = new ButtonUI(g, g->getTexture("MenuReturnButton"), [this](Game* game) { back(game); }, { 0, 1, 2, 2, 2 }, 7);
	_backButton->setPosition(CAMERA_RESOLUTION_X / 2 + 150 - _backButton->getW(), CAMERA_RESOLUTION_Y - _backButton->getH() - 20);

	//Pantalla completa
	_screenButton = new ButtonUI(g, g->getTexture("MenuFullScreenButton"), [this](Game* game) { fullScreen(game); }, { 0, 1, 2, 2, 2 }, 6);
	_screenButton->setPosition(CAMERA_RESOLUTION_X / 2 - 150, _backButton->getY());

	bool IsFullscreen = SDL_GetWindowFlags(g->getWindow()) & SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (IsFullscreen)
		_screenButton->setFrames({ 3, 4, 5, 0, 5 });
		
	_lessVolume->setNextButtons({ _moreVolume, _screenButton, _moreVolume, _lessSFXVolume });
	_moreVolume->setNextButtons({ _lessVolume, _backButton, _lessVolume, _moreSFXVolume });
	_lessSFXVolume->setNextButtons({ _moreSFXVolume, _lessVolume, _moreSFXVolume, _lessBright });
	_moreSFXVolume->setNextButtons({ _lessSFXVolume, _moreVolume, _lessSFXVolume, _moreBright });
	_lessBright->setNextButtons({ _moreBright, _lessSFXVolume, _moreBright, _screenButton });
	_moreBright->setNextButtons({ _lessBright, _moreSFXVolume, _lessBright, _backButton });
	_screenButton->setNextButtons({ _backButton, _lessBright, _backButton, _lessVolume });
	_backButton->setNextButtons({ _screenButton, _moreBright, _screenButton, _moreVolume });

	//----TEXTOS----//

	//Valores
	_volumeText = new TextUI(g, "100", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_volumeText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeText->getW() / 2,
							_moreVolume->getY() + buttonH / 2 - _volumeText->getH() / 2);

	float _volume = g->getSoundManager()->getMusicVolume() / 128.0;
	_volumeText->setText(to_string(valueToWrite(_volume)));

	_volumeSFXText = new TextUI(g, "100", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_volumeSFXText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeSFXText->getW() / 2,
								_moreSFXVolume->getY() + buttonH / 2 - _volumeSFXText->getH() / 2);

	_volume = g->getSoundManager()->getGeneralVolume() / 128.0;
	_volumeSFXText->setText(to_string(valueToWrite(_volume)));


	//Nombres
	_nameVolumeText = new TextUI(g, "Volumen Musica", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_nameVolumeText->setPosition(CAMERA_RESOLUTION_X / 2 - _nameVolumeText->getW() / 2,
								_moreVolume->getY() - 30);

	_nameVolumeSFXText = new TextUI(g, "Volumen Efectos", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_nameVolumeSFXText->setPosition(CAMERA_RESOLUTION_X / 2 - _nameVolumeSFXText->getW() / 2,
									_moreSFXVolume->getY() - 30);

	_nameBrightText = new TextUI(g, "Brillo", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_nameBrightText->setPosition(CAMERA_RESOLUTION_X / 2 - _nameBrightText->getW() / 2,
								_moreBright->getY() - 30);

	addChild(_moreVolume);
	addChild(_lessVolume);
	addChild(_moreSFXVolume);
	addChild(_lessSFXVolume);
	addChild(_moreBright);
	addChild(_lessBright);
	addChild(_backButton);
	addChild(_screenButton);
	addChild(_volumeSFXText);
	addChild(_volumeText);
	addChild(_nameVolumeSFXText);
	addChild(_nameVolumeText);
	addChild(_nameBrightText);

	_visible = false;

	_selectedButton = _lessVolume;
	if (_game->usingJoystick())
	{
		_selectedButton->setSelected(true);
		SDL_ShowCursor(false);
		SDL_WarpMouseGlobal(0, 0);
	}
}


OptionsPanel::~OptionsPanel()
{
}

bool OptionsPanel::handleEvent(const SDL_Event& event)
{
	if (_visible)
	{
		if (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			back(_game);
			return true;
		}
	}
	return PanelUI::handleEvent(event);;
}

void OptionsPanel::moreVolume(Game * g)
{
	float _volume = g->getSoundManager()->getMusicVolume() / 128.0;
	if (_volume + 0.1 > 1)
		_volume = 1;
	else
		_volume += 0.1;

	g->getSoundManager()->setMusicVolume(_volume);

	_volumeText->setText(to_string(valueToWrite(_volume)));

	_volumeText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeText->getW() / 2,
		_moreVolume->getY() + buttonH / 2 - _volumeText->getH() / 2);
}

void OptionsPanel::lessVolume(Game * g)
{
	float _volume = g->getSoundManager()->getMusicVolume() / 128.0;
	if (_volume - 0.1 < 0)
		_volume = 0;
	else
		_volume -= 0.1;

	g->getSoundManager()->setMusicVolume(_volume);

	_volumeText->setText(to_string(valueToWrite(_volume)));

	_volumeText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeText->getW() / 2,
		_moreVolume->getY() + buttonH / 2 - _volumeText->getH() / 2);
}

void OptionsPanel::moreSFXVolume(Game * g)
{
	float _sfxVolume = g->getSoundManager()->getGeneralVolume() / 128.0;
	if (_sfxVolume + 0.1 > 1)
		_sfxVolume = 1;
	else
		_sfxVolume += 0.1;

	g->getSoundManager()->setGeneralVolume(_sfxVolume);

	_volumeSFXText->setText(to_string(valueToWrite(_sfxVolume)));
	_volumeSFXText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeSFXText->getW() / 2,
		_moreSFXVolume->getY() + buttonH / 2 - _volumeSFXText->getH() / 2);
}

void OptionsPanel::lessSFXVolume(Game * g)
{
	float _sfxVolume = g->getSoundManager()->getGeneralVolume() / 128.0;
	if (_sfxVolume - 0.1 < 0)
		_sfxVolume = 0;
	else
		_sfxVolume -= 0.1;

	g->getSoundManager()->setGeneralVolume(_sfxVolume);

	_volumeSFXText->setText(to_string(valueToWrite(_sfxVolume)));
	_volumeSFXText->setPosition(CAMERA_RESOLUTION_X / 2 - _volumeSFXText->getW() / 2,
		_moreSFXVolume->getY() + buttonH / 2 - _volumeSFXText->getH() / 2);
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
	if (_menu)
	{
		g->getCurrentState()->getMainCamera()->setBackGround(new BackGround(g->getTexture("BgMenu"), g->getCurrentState()->getMainCamera()));
		g->getCurrentState()->getMenuHUD()->getMainMenuPanel()->setVisible(true);
	}
	else
	{
		g->getCurrentState()->getMainCamera()->setBackGround(new BackGround(g->getTexture("BgPauseMenu"), g->getCurrentState()->getMainCamera()));
		g->getCurrentState()->getPauseHUD()->getPausePanel()->setVisible(true);
	}
}

void OptionsPanel::fullScreen(Game* g)
{
	bool IsFullscreen = SDL_GetWindowFlags(g->getWindow()) & SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (IsFullscreen)
	{
		_screenButton->setFrames({ 0, 1, 2, 3, 2 });
		SDL_SetWindowFullscreen(g->getWindow(), 0);
	}
	else
	{
		_screenButton->setFrames({ 3, 4, 5, 0, 5 });
		SDL_SetWindowFullscreen(g->getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
}

int OptionsPanel::valueToWrite(float val)
{
	val *= 10;
	val = ceil(val);
	val *= 10;
	val = ceil(val);

	int vol = val;

	return vol;
}