#include "MenuState.h"
#include "PlayState.h"
#include "ParallaxBackGround.h"

MenuState::MenuState(Game* g) : GameState(g)
{
	//Show cursor
	SDL_ShowCursor(true);

	int buttonH = g->getTexture("Play")->getH()*BUTTON_SCALE;
	int buttonW = g->getTexture("Play")->getW()*BUTTON_SCALE;

	_stages.push_back(new MenuButton(Vector2D(GAME_RESOLUTION_X / 2 - buttonW / 2, GAME_RESOLUTION_Y / 2 - buttonH + 50), g->getTexture("Play"), g, startGame));
	_stages.push_back(new MenuButton(Vector2D(GAME_RESOLUTION_X / 2 - buttonW / 2, GAME_RESOLUTION_Y / 2 + buttonH + 50), g->getTexture("Exit"), g, exitGame));

	//Camera BackGound
	ParallaxBackGround* a = new ParallaxBackGround(_mainCamera);
	a->addLayer(new ParallaxLayer(g->getTexture("BgMenu"), _mainCamera, 0));
	_mainCamera->setBackGround(a);
}

void MenuState::startGame(Game * g)
{
	g->changeState(new PlayState(g));
}

void MenuState::exitGame(Game * g)
{
	g->setExit(true);
}