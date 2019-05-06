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

	//Cursor
	_cursor = new Cursor(g);
	SDL_ShowCursor(false);

	//Anyadir a elementos
	addUIElement(_playerPanel);
	addUIElement(_bossPanel);
	addUIElement(_shopMenu);
	addUIElement(_dialoguePanel);
	addUIElement(_popUpPanel);
	addUIElement(_cursor);

	//Asignaciones
	_shopMenu->setDialoguePanel(_dialoguePanel);
}