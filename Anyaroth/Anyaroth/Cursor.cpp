#include "Cursor.h"
#include "ImageUI.h"
#include "Game.h"

Cursor::Cursor(Game* game) : ImageUI(game, game->getTexture("GunCursor"))
{
	
}

void Cursor::update(const double& deltaTime)
{
	Vector2D offset = { (double)getImage()->getW() / 2, (double)getImage()->getH() / 2 };
	Vector2D mousePos = _game->getCurrentState()->getMousePositionInWorld() - _game->getCurrentState()->getMainCamera()->getCameraPosition() - offset;
	setPosition(mousePos.getX(), mousePos.getY());
}