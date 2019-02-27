#include "PlayStateHUD.h"


PlayStateHUD::PlayStateHUD(Game * g)
{
	_lifeBar = ImageUI(g->getTexture("Ammo"));
	_lifeBar.setPosition(20, 20);
	addUIElement(&_lifeBar);
}

PlayStateHUD::~PlayStateHUD()
{

}
