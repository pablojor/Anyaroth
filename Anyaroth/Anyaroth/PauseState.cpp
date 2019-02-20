#include "PauseState.h"

PauseState::PauseState(Game* g) : GameState(g) 
{
	int buttonH = g->getTexture("Continue")->getH()*BUTTON_SCALE;
	int buttonW = g->getTexture("Continue")->getW()*BUTTON_SCALE;

	_stages.push_back(new MenuButton(Vector2D(g->GAME_RESOLUTION_X / 2 - buttonW / 2, g->GAME_RESOLUTION_Y / 2 - buttonH), g->getTexture("Continue"), g, Continue));
	_stages.push_back(new MenuButton(Vector2D(g->GAME_RESOLUTION_X / 2 - buttonW / 2, g->GAME_RESOLUTION_Y / 2 + buttonH), g->getTexture("Menu"), g, MainMenu));
}

PauseState::~PauseState()
{
}

void PauseState::Continue(Game * g)
{
	g->popState();
}

void PauseState::MainMenu(Game * g)
{
	g->changeState(Menu);
}