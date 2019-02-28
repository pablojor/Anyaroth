#include "PlayerPanel.h"
#include "Game.h"


PlayerPanel::PlayerPanel(Game* game) : PanelUI(game)
{
	//Inicializamos
	_lifeBar = new ImageUI(game, game->getTexture("Ammo"));
	_ammoViewer = new TextUI(game, "Ammo: " + to_string(29), game->getFont("ARIAL12"), 12, { 255, 255, 255, 255 });

	//Añadimos al panel
	addChild(_lifeBar);
	addChild(_ammoViewer);

}


PlayerPanel::~PlayerPanel()
{
}
