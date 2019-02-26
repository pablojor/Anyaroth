#include "MenuState.h"
#include "PlayState.h"

MenuState::MenuState(Game* g) : GameState(g)
{
	int buttonH = g->getTexture("Play")->getH()*BUTTON_SCALE;
	int buttonW = g->getTexture("Play")->getW()*BUTTON_SCALE;

	_stages.push_back(new MenuButton(Vector2D(g->GAME_RESOLUTION_X / 2 - buttonW / 2, g->GAME_RESOLUTION_Y / 2 - buttonH), g->getTexture("Play"), g, startGame));
	_stages.push_back(new MenuButton(Vector2D(g->GAME_RESOLUTION_X / 2 - buttonW / 2, g->GAME_RESOLUTION_Y / 2 + buttonH), g->getTexture("Exit"), g, exitGame));
}

MenuState::~MenuState()
{
}

void MenuState::startGame(Game * g)
{
	g->changeState(new PlayState(g));
}

void MenuState::exitGame(Game * g)
{
	g->setExit(true);
}