#include "CreditsStateHUD.h"
#include "Game.h"
#include "Camera.h"


CreditsStateHUD::CreditsStateHUD(Game* game)
{
	_menuButton = new ButtonUI(game, game->getTexture("MenuButtons"), [this](Game* game) { goToMenu(game); }, { 0,1,2,2 });
	_buttonText = new TextUI(game, "Menu", game->getFont("ARIAL12"), 12, 0, 0, { 0, 0, 0, 0 });

	_text = new TextUI(game, "THANKS FOR PLAYING", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_text->setScale(2);
	_text->setPosition(CAMERA_RESOLUTION_X / 2 - _text->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 - 20);

	_menuButton->setPosition(CAMERA_RESOLUTION_X / 2 - _menuButton->getW() / 2, _text->getPosition().getY() + 45);

	_buttonText->setPosition(_menuButton->getX() + _menuButton->getW() / 2 - _buttonText->getW() / 2, _menuButton->getY() + _menuButton->getH() / 2 - _buttonText->getH() / 2);

	addUIElement(_menuButton);
	addUIElement(_buttonText);
	addUIElement(_text);
}


CreditsStateHUD::~CreditsStateHUD()
{
}


void CreditsStateHUD::goToMenu(Game* game)
{
	game->popState();
	game->changeState(new MenuState(game));
}

