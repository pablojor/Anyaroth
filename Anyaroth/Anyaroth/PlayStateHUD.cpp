#include "PlayStateHUD.h"
#include "Game.h"

ShopMenu* PlayStateHUD::_shopMenu = nullptr;

PlayStateHUD::PlayStateHUD(Game * g)
{
	//Panel del jugador
	_playerPanel = new PlayerPanel(g);

	//Panel del Boss
	_bossPanel = new BossPanel(g);

	//Panel de Tienda
	_shopMenu = new ShopMenu(g);

	//Panel de dialogos
	_dialoguePanel = new DialoguePanel(g);

	//Anyadir a elementos
	addUIElement(_playerPanel);
	addUIElement(_bossPanel);
	addUIElement(_shopMenu);
	addUIElement(_dialoguePanel);
}

void PlayStateHUD::closeShopMenu(Game * game)
{
	_shopMenu->setVisible(false);
}
