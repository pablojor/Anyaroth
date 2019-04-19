#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "BackGround.h"

MenuState::MenuState(Game* g) : GameState(g)
{
	//Show cursor
	SDL_ShowCursor(true);

	//HUD
	_menuHud = new MenuStateHUD(g);
	setCanvas(_menuHud);

	//Camera BackGound
	_mainCamera->setBackGround(new BackGround(g->getTexture("BgMenu"), _mainCamera));

	//g->getSoundManager()->playMusic("bgMusic", true);
}