#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "BackGround.h"

MenuState::MenuState(Game* g) : GameState(g)
{
	//Show cursor
	SDL_ShowCursor(true);

	//HUD
	_menuHUD = new MenuStateHUD(g);
	setCanvas(_menuHUD);

	//Camera BackGound
	_mainCamera->setBackGround(new BackGround(g->getTexture("BgMenu"), _mainCamera));

	//g->getSoundManager()->playMusic("bgMusic", true);
}

void MenuState::startGame(Game * g)
{
	g->changeState(new PlayState(g));
}

void MenuState::exitGame(Game * g)
{
	g->setExit(true);
}