#include "MenuState.h"

MenuState::MenuState(Game* g) : GameState(g)
{
	_stages.push_back(new MenuButton(Vector2D(WIN_WIDTH / 2, 100), 100, 50, g->getTexture("button"), g, startGame));
	_stages.push_back(new MenuButton(Vector2D(WIN_WIDTH / 2 + 200, 100), 100, 50, g->getTexture("button"), g, exitGame));
}

MenuState::~MenuState()
{
}

void MenuState::startGame(Game * g)
{
	g->changeState(Play);
}

void MenuState::exitGame(Game * g)
{
	g->changeState(Menu);
}