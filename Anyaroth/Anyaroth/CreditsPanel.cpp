#include "CreditsPanel.h"
#include "Game.h"
#include "ImageUI.h"


CreditsPanel::CreditsPanel(Game* g) : PanelUI(g)
{
	_menuButton = new ButtonUI(g, g->getTexture("ExitButton"), [this](Game* game) { goToMenu(game); }, { 0,1,2,2 });
	//_buttonText = new TextUI(g, "Menu", g->getFont("ARIAL12"), 12, 0, 0, { 0, 0, 0, 0 });

	ImageUI* bg = new ImageUI(g, g->getTexture("DemoCredits"));
	bg->setPosition(0,0/*CAMERA_RESOLUTION_X / 2 - bg->getW() / 2, CAMERA_RESOLUTION_Y / 2 - bg->getH() / 2 - 20*/);

	_text = new TextUI(g, "Rebellion Status Report: With the defeat of general Spenta Manyu, carried out by one", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_text->setScale(0.6);
	_text->setPosition(CAMERA_RESOLUTION_X / 2 - _text->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 - 20 - 35);
	TextUI* text2 = new TextUI(g, "of our most powerful comrades, victory is just a matter of time.", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text2->setScale(0.6);
	text2->setPosition(CAMERA_RESOLUTION_X / 2 - _text->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 - 10 - 35);
	TextUI* text3 = new TextUI(g, "However, we must not rest until we finally overthrow the Queen.", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text3->setScale(0.6);
	text3->setPosition(CAMERA_RESOLUTION_X / 2 - _text->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 + 10 - 35);
	TextUI* text4 = new TextUI(g, "Don't lose track of our planet's fate, follow us on social networks.", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text4->setScale(0.6);
	text4->setPosition(CAMERA_RESOLUTION_X / 2 - _text->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 + 30 - 35);
	TextUI* text5 = new TextUI(g, "The anyas need you!", g->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	text5->setScale(0.6);
	text5->setPosition(CAMERA_RESOLUTION_X / 2 - _text->getW() / 2, CAMERA_RESOLUTION_Y / 2 - _text->getH() / 2 + 40 - 35);

	ImageUI* twitter = new ImageUI(g, g->getTexture("DemoTwitter"));
	twitter->setPosition(_text->getX() + 190, _text->getY() + 66);
	twitter->setSize(74, 13);

	_menuButton->setPosition(CAMERA_RESOLUTION_X / 2 - _menuButton->getW() / 2 + 210, _text->getPosition().getY() + 160);

	//_buttonText->setPosition(_menuButton->getX() + _menuButton->getW() / 2 - _buttonText->getW() / 2, _menuButton->getY() + _menuButton->getH() / 2 - _buttonText->getH() / 2);


	_selectedButton = _menuButton;
	_selectedButton->setSelected(true);

	addChild(bg);
	addChild(_menuButton);
	//addChild(_buttonText);
	addChild(twitter);
	addChild(_text);
	addChild(text2);
	addChild(text3);
	addChild(text4);
	addChild(text5);
}


CreditsPanel::~CreditsPanel()
{
}

void CreditsPanel::goToMenu(Game* game)
{
	game->popState();
	game->changeState(new MenuState(game));
}