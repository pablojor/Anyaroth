#include "DepotPanel.h"
#include "Player.h"
#include "ShopMenu.h"

ShopItem* DepotPanel::_selectedItem = nullptr;
Player* DepotPanel::_player = nullptr; 
ShopItem* DepotPanel::_firstWeapon = nullptr;
ShopItem* DepotPanel::_secondWeapon = nullptr;
ShopItem* DepotPanel::_meleeWeapon = nullptr;

DepotPanel::DepotPanel(Game* game) : PanelUI(game)
{
	//----MARCOS----//

	_depotFrame = new ImageUI(game, game->getTexture("ShopPanel"), 5, 5);
	_depotFrame->setSize(_depotFrame->getW() * 2, _depotFrame->getH()); //POSIBLEMENTE PROVISIONAL
	_equipmentFrame = new ImageUI(game, game->getTexture("ShopPanel"), _depotFrame->getX() + _depotFrame->getW() + 10, 5);
	_equipmentFrame->setSize(_equipmentFrame->getW() * 0.75, _equipmentFrame->getH() * 0.75);

		//Añadir como hijo
	addChild(_depotFrame);
	addChild(_equipmentFrame);

	//----BOTON DE SALIR----//

	_exitButton = new ButtonUI(game, game->getTexture("Button"), ShopMenu::closeDepotPanel, { 0,1,2,3 });
	_exitButton->setPosition(_depotFrame->getX(), _depotFrame->getY() + _depotFrame->getH() + 2);
	_exitButton->setSize(_depotFrame->getW(), _exitButton->getH() + 4); //POSIBLEMENTE PROVISIONAL

		//Añadir como hijo
	addChild(_exitButton);

	//----EQUIPAMIENTO----//

		//Crear celdas
	int distanceBetweenSlots = 10;
	int itemWidth = (_equipmentFrame->getW() / 2) - (distanceBetweenSlots + distanceBetweenSlots / 2);
	int itemHeight = itemWidth;

	_firstWeapon = new ShopItem(game, game->getTexture("InfoIcon"));
	_firstWeapon->setSize(itemWidth, itemHeight); //POSIBLEMENTE PROVISIONAL
	_firstWeapon->setPosition(_equipmentFrame->getX() + distanceBetweenSlots,
							_equipmentFrame->getY() + _equipmentFrame->getH() / 4 + distanceBetweenSlots * 0.5);

	_secondWeapon = new ShopItem(game, game->getTexture("Dash"));
	_secondWeapon->setSize(itemWidth, itemHeight); //POSIBLEMENTE PROVISIONAL
	_secondWeapon->setPosition(_firstWeapon->getX() + _firstWeapon->getW() + distanceBetweenSlots, 
							_firstWeapon->getY());

	_meleeWeapon = new ShopItem(game, game->getTexture("InfoIcon"));
	_meleeWeapon->setSize(itemWidth, itemHeight); //POSIBLEMENTE PROVISIONAL
	_meleeWeapon->setPosition(_equipmentFrame->getX() + _equipmentFrame->getW() / 2 - itemWidth / 2, 
								_firstWeapon->getY() + _firstWeapon->getH() + distanceBetweenSlots);

		//Callbacks
	_firstWeapon->onDown(setDistanceWeapon);
	_secondWeapon->onDown(setDistanceWeapon);
	_meleeWeapon->onDown(setMeleeWeapon);

		//Añadir como hijo
	addChild(_firstWeapon);
	addChild(_secondWeapon);
	addChild(_meleeWeapon);

	//----BOTON DE CAMBIO DE EQUIPAMIENTO----//

	_changeButton = new ButtonUI(game, game->getTexture("Button"), changeEquipedGuns, { 0,1,2,3 });
	_changeButton->setSize(itemWidth * 0.75, itemHeight / 2); //POSIBLEMENTE PROVISIONAL
	_changeButton->setPosition(_equipmentFrame->getX() + _equipmentFrame->getW() / 2 - _changeButton->getW() / 2,
								_firstWeapon->getY() - _changeButton->getH() - distanceBetweenSlots * 0.25);

		//Añadir como hijo
	addChild(_changeButton);

	//----ALMACEN----//
}

void DepotPanel::changeEquipedGuns(Game* game)
{
	_player->swapGun();

	auto* firstWeapon = _firstWeapon;
	_firstWeapon = _secondWeapon;
	_secondWeapon = firstWeapon;
}

void DepotPanel::selectDistanceWeapon(Game* game, ShopItem* item)
{
	
}

void DepotPanel::setDistanceWeapon(Game* game)
{
	if (_selectedItem != nullptr)
		cout << "cambio arma";
}


void DepotPanel::selectMeleeWeapon(Game* game)
{

}

void DepotPanel::setMeleeWeapon(Game* game)
{
	if (_selectedItem != nullptr)
		cout << "cambio melee";
}
