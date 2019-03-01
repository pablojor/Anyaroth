#include "AmmoViewer.h"
#include "Game.h"



AmmoViewer::AmmoViewer(Game* game, int xPos, int yPos) : PanelUI(game)
{
	_clipText = new TextUI(game, to_string(ammoClip), game->getFont("ARIAL12"), 12, xPos, yPos, { 255, 255, 255, 255 });
	_magazineText = new TextUI(game," / " + to_string(ammoMagazine), game->getFont("ARIAL12"), 12, xPos + _clipText->getW(), yPos, { 255, 255, 255, 255 });
}

void AmmoViewer::updateAspect()
{

}

