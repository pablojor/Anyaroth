#include "PlayStateHUD.h"
#include "Game.h"


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

	//Panel emergente
	_popUpPanel = new PopUpPanel(g);
	_popUpPanel->setVisible(false);

	//Anyadir a elementos
	addUIElement(_playerPanel);
	addUIElement(_bossPanel);
	addUIElement(_shopMenu);
	addUIElement(_dialoguePanel);
	addUIElement(_popUpPanel);

	//Asignaciones
	_shopMenu->setDialoguePanel(_dialoguePanel);
}

