#include "PausePanel.h"
#include "Game.h"

PausePanel::PausePanel(Game* g) : PanelUI(g)
{
	//----BOTONES----//

	_playButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { continueGame(game); }, { 0, 1, 2, 2, 2 });
	int buttonH = _playButton->getH(),
		buttonW = _playButton->getW();
	_playButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 - buttonH + 50);

	_optionsButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { options(game); }, { 0, 1, 2, 2, 2 }, 1);
	_optionsButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 + buttonH + 50);

	_menuButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { returnMenu(game); }, { 0, 1, 2, 2, 2 }, 2);
	_menuButton->setPosition(CAMERA_RESOLUTION_X / 2 - buttonW / 2, CAMERA_RESOLUTION_Y / 3 + buttonH + 100);

	//----TEXTOS----//

	_playText = new TextUI(g, "Continue", g->getFont("ARIAL12"), 12);
	_playText->setPosition(CAMERA_RESOLUTION_X / 2 - _playText->getW() / 2,
							_playButton->getY() + buttonH / 2 - _playText->getH() / 2);

	_optionsText = new TextUI(g, "Options", g->getFont("ARIAL12"), 12);
	_optionsText->setPosition(_optionsButton->getX() + buttonW / 2 - _optionsText->getW() / 2,
								_optionsButton->getY() + buttonH / 2 - _optionsText->getH() / 2);

	_menuText = new TextUI(g, "Menu", g->getFont("ARIAL12"), 12);
	_menuText->setPosition(_menuButton->getX() + buttonW / 2 - _menuText->getW() / 2,
							_menuButton->getY() + buttonH / 2 - _menuText->getH() / 2);

	_playButton->setNextButtons({ _menuButton, _menuButton, _optionsButton, _optionsButton });
	_optionsButton->setNextButtons({ _playButton, _playButton, _menuButton, _menuButton });
	_menuButton->setNextButtons({ _optionsButton, _optionsButton, _playButton, _playButton });

	addChild(_playButton);
	addChild(_optionsButton);
	addChild(_menuButton);
	addChild(_playText);
	addChild(_optionsText);
	addChild(_menuText);

	_selectedButton = _playButton;

	if (_game->usingJoystick())
	{
		_selectedButton->setSelected(true);
		SDL_ShowCursor(false);
		SDL_WarpMouseGlobal(0, 0);
	}
}

PausePanel::~PausePanel()
{
}

bool PausePanel::handleEvent(const SDL_Event& event)
{
	if (_visible)
	{
		if (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			continueGame(_game);
			return true;
		}
	}
	return PanelUI::handleEvent(event);;
}

void PausePanel::continueGame(Game * g)
{
	SDL_ShowCursor(false);
	g->getSoundManager()->resumeMusic();
	g->setTimestep(FRAME_RATE / 1000.0f);
	g->popState();
}

void PausePanel::options(Game * g)
{
	_visible = !_visible; 
	g->getCurrentState()->getMainCamera()->setBackGround(new BackGround(g->getTexture("BgOptionsMenu"), g->getCurrentState()->getMainCamera()));
	g->getCurrentState()->getPauseHUD()->getOptionsPanel()->setVisible(true);
}

void PausePanel::returnMenu(Game * g)
{
	g->getSoundManager()->stopMusic();
	g->setTimestep(FRAME_RATE / 1000.0f);
	g->popState();
	g->changeState(new MenuState(g));
}