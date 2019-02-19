#include "PauseState.h"

PauseState::PauseState(Game* g) : GameState(g) 
{
	_stages.push_back(new MenuButton(Vector2D(WIN_WIDTH / 2, 100), 100, 50, g->getTexture("button"), g, MainMenu));
	_stages.push_back(new MenuButton(Vector2D(WIN_WIDTH / 2 + 200, 100), 100, 50, g->getTexture("button"), g, Continue));
}

PauseState::~PauseState()
{
}

void PauseState::MainMenu(Game * g)
{
	g->changeState(Menu);
}

void PauseState::Continue(Game * g)
{
	g->changeState(Play);
}