#include "PauseState.h"
#include "MenuState.h"

PauseState::PauseState(Game* g) : GameState(g)
{
	//Show cursor
	SDL_ShowCursor(true);

	int buttonH = g->getTexture("Continue")->getH()*BUTTON_SCALE;
	int buttonW = g->getTexture("Continue")->getW()*BUTTON_SCALE;

	_stages.push_back(new MenuButton(Vector2D(GAME_RESOLUTION_X / 2 - buttonW / 2, GAME_RESOLUTION_Y / 2 - buttonH), g->getTexture("Continue"), g, Continue));
	_stages.push_back(new MenuButton(Vector2D(GAME_RESOLUTION_X / 2 - buttonW / 2, GAME_RESOLUTION_Y / 2 + buttonH), g->getTexture("Menu"), g, MainMenu));
}

void PauseState::Continue(Game * g)
{
	g->getWorld()->Step(1 / 60.0, 8, 3);
	g->popState();
}

void PauseState::MainMenu(Game * g)
{
	g->popState();
	g->changeState(new MenuState(g));
}