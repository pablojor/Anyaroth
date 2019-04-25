#include "CreditsPanel.h"
#include "Game.h"


CreditsPanel::CreditsPanel(Game* g) : PanelUI(g)
{
	_menuButton = new ButtonUI(g, g->getTexture("MenuButtons"), [this](Game* game) { goToMenu(game); }, { 0,1,2,2 });
	_buttonText = new TextUI(g, "Menu", g->getFont("ARIAL12"), 12, 0, 0, { 0, 0, 0, 0 });

	_text = new TextUI(g, "THANKS FOR PLAYING", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_text->setScale(2);
	_text->setPosition(CAMERA_RESOLUTION_X / 2 - _text->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 - 20);

	_menuButton->setPosition(CAMERA_RESOLUTION_X / 2 - _menuButton->getW() / 2, _text->getPosition().getY() + 45);

	_buttonText->setPosition(_menuButton->getX() + _menuButton->getW() / 2 - _buttonText->getW() / 2, _menuButton->getY() + _menuButton->getH() / 2 - _buttonText->getH() / 2);


	_selectedButton = _menuButton;
	_selectedButton->setSelected(true);

	addChild(_menuButton);
	addChild(_buttonText);
	addChild(_text);
}


CreditsPanel::~CreditsPanel()
{
}

void CreditsPanel::goToMenu(Game* game)
{
	game->popState();
	game->changeState(new MenuState(game));
}