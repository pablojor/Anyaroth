#include "DepotPanel.h"
#include "Player.h"
#include "ShopMenu.h"
#include <functional>
#include <algorithm>
#include "Game.h"
#include "WeaponManager.h"

DepotPanel::DepotPanel(Game* game) : PanelUI(game)
{
	//----MARCOS----//

	_depotFrame = new ImageUI(game, game->getTexture("DepotPanel"), 21, 29);
	_equipmentFrame = new ImageUI(game, game->getTexture("EquipPanel"), _depotFrame->getX() + _depotFrame->getW() + 5, _depotFrame->getY() + 14);

		//Añadir como hijo
	addChild(_depotFrame);
	addChild(_equipmentFrame);

	//----BOTON DE SALIR----//

	_exitButton = new ButtonUI(game, game->getTexture("ReturnButton"), nullptr, { 0,1,1,1 });
	_exitButton->setPosition(CAMERA_RESOLUTION_X - _exitButton->getW() - 12, 188 - 1 - _exitButton->getH());

		//Añadir como hijo
	addChild(_exitButton);

	//----EQUIPAMIENTO----//

		//Crear celdas
	_firstWeaponFrame = new ShopItem(game, game->getTexture("ItemFrame"));
	_firstWeaponFrame->setPosition(_equipmentFrame->getX() + 8,
									_equipmentFrame->getY() + 8);
	_firstWeaponFrame->setItemInfo({ -1, "arma1", 0, 14, 25, 10, GunType::Pistol_Weapon, true, true });

	_secondWeaponFrame = new ShopItem(game, game->getTexture("ItemFrame"));
	_secondWeaponFrame->setPosition(_firstWeaponFrame->getX() + _firstWeaponFrame->getW() + 26,
									_firstWeaponFrame->getY());
	_secondWeaponFrame->setItemInfo({ -1, "arma2", 0, 14, 25, 10, GunType::Pistol_Weapon, true, true });

	_meleeWeaponFrame = new ShopItem(game, game->getTexture("ItemFrame"));
	_meleeWeaponFrame->setPosition(_equipmentFrame->getX() + _equipmentFrame->getW() / 2 - _meleeWeaponFrame->getW() / 2,
							_firstWeaponFrame->getY() + _firstWeaponFrame->getH() + distanceBetweenEquipmentSlots);

		//Callbacks
	_firstWeaponFrame->onDown([this](Game* game) { setDistanceWeapon(game, _firstWeaponFrame); });
	_secondWeaponFrame->onDown([this](Game* game) { setDistanceWeapon(game, _secondWeaponFrame); });
	_meleeWeaponFrame->onDown([this](Game* game) { setMeleeWeapon(game, _meleeWeaponFrame); });

		//Añadir como hijo
	addChild(_firstWeaponFrame);
	addChild(_secondWeaponFrame);
	addChild(_meleeWeaponFrame);

	//----BOTON DE CAMBIO DE EQUIPAMIENTO----//

	_changeButton = new ButtonUI(game, game->getTexture("ChangeButton"), [this](Game* game) {changeEquipedGuns(game); }, { 0,1,1,1 });
	_changeButton->setPosition(_equipmentFrame->getX() + 45,
								_equipmentFrame->getY() + 17);

		//Añadir como hijo
	addChild(_changeButton);

	//----ALMACEN----//
}

void DepotPanel::inicializeCallback(ShopMenu * menu)
{
	_exitButton->onDown([menu](Game* game) { menu->closeDepotPanel(game); });
}

void DepotPanel::setItems(list<ShopItem*>* list)
{
	_items = list;

	for (auto it : *_items)
		addChild(it);
}

void DepotPanel::removeItems()
{
	for (auto it : *_items)
		removeChild(it);
}

void DepotPanel::openDepotPanel()
{
	for (auto it : *_items)
	{
		it->onDown([this, it](Game* game) {	selectItem(game, it); });
	}

	reorderDepot();
	setVisible(true);
}

void DepotPanel::closeDepotPanel()
{
	setVisible(false);
	_selectedItem = nullptr;
}

void DepotPanel::reorderDepot()
{
	int posIniX = 11,
		posIniY = 9,
		distX = 9,
		distY = 4;

	ShopItem* primItem = nullptr;

	auto it = (*_items).begin();
	int fil = 0;
	while (fil < itemsPerCol && it != (*_items).end())
	{
		int col = 0;
		while (it != (*_items).end() && col < itemsPerRow)
		{
			auto item = *it;
			auto info = item->getItemInfo();

			if (info._sold && !info._equiped)
			{
				item->setVisible(true);

				if (primItem == nullptr)
				{
					item->setPosition(_depotFrame->getX() + posIniX, _depotFrame->getY() + posIniY);
					primItem = item;
				}
				else
					item->setPosition(primItem->getX() + (primItem->getW() + distX) * col, primItem->getY() + (primItem->getH() + distY) * fil);

				col++;
			}
			else
				item->setVisible(false);

			it++;
		}
		fil++;
	}
}

void DepotPanel::changeEquipedGuns(Game* game)
{
	_player->swapGun();

	auto firstWeaponInfo = _firstWeaponFrame->getItemInfo();
	auto firstWeaponImage = _firstWeaponFrame->getItemImage();

	_firstWeaponFrame->setItemInfo(_secondWeaponFrame->getItemInfo());
	_firstWeaponFrame->setItemImage(_secondWeaponFrame->getItemImage());

	_secondWeaponFrame->setItemInfo(firstWeaponInfo);
	_secondWeaponFrame->setItemImage(firstWeaponImage);
}

void DepotPanel::selectItem(Game * game, ShopItem* item)
{
	_selectedItem = item;
}

void DepotPanel::setDistanceWeapon(Game* game, ShopItem* item)
{
	if (_selectedItem != nullptr)
	{
		swapItems(item);
		reorderDepot();
		_selectedItem = nullptr;
	}
}

void DepotPanel::setMeleeWeapon(Game* game, ShopItem* item)
{
	if (_selectedItem != nullptr)
	{
		swapItems(item);
		reorderDepot();
		_selectedItem = nullptr;
	}
}

void DepotPanel::swapItems(ShopItem* _equiped)
{
	//Cambiamos la info
	auto infoSelected = _selectedItem->getItemInfo();
	auto otherInfo = _equiped->getItemInfo();
	infoSelected._equiped = true;
	otherInfo._equiped = false;

	_selectedItem->setItemInfo(otherInfo);
	_equiped->setItemInfo(infoSelected);

	//Cambio de texturas
	auto imageSelect = _selectedItem->getImage();
	auto imageOther = _equiped->getImage();
	_selectedItem->setImage(imageOther);
	_equiped->setImage(imageSelect);

	//Equipo arma
	Gun* newGun = WeaponManager::getWeapon(_game, _equiped->getItemInfo()._type);
	if (_equiped == _firstWeaponFrame) 
		_player->changeCurrentGun(newGun);
	else if (_equiped == _secondWeaponFrame)
		_player->changeOtherGun(newGun);
}


