#include "DepotPanel.h"
#include "Player.h"
#include "ShopMenu.h"
#include <functional>
#include <algorithm>
#include "Game.h"

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
	itemEquipWidth = (_equipmentFrame->getW() / 2) - (10 + 5),
	itemEquipHeight = itemEquipWidth;

	_firstWeapon = new ShopItem(game, game->getTexture("InfoIcon"));
	_firstWeapon->setSize(itemEquipWidth, itemEquipHeight); //POSIBLEMENTE PROVISIONAL
	_firstWeapon->setPosition(_equipmentFrame->getX() + distanceBetweenEquipmentSlots,
		_equipmentFrame->getY() + _equipmentFrame->getH() / 4 + distanceBetweenEquipmentSlots * 0.5);

	_secondWeapon = new ShopItem(game, game->getTexture("Dash"));
	_secondWeapon->setSize(itemEquipWidth, itemEquipHeight); //POSIBLEMENTE PROVISIONAL
	_secondWeapon->setPosition(_firstWeapon->getX() + _firstWeapon->getW() + distanceBetweenEquipmentSlots,
		_firstWeapon->getY());

	_meleeWeapon = new ShopItem(game, game->getTexture("InfoIcon"));
	_meleeWeapon->setSize(itemEquipWidth, itemEquipHeight); //POSIBLEMENTE PROVISIONAL
	_meleeWeapon->setPosition(_equipmentFrame->getX() + _equipmentFrame->getW() / 2 - itemEquipWidth / 2,
							_firstWeapon->getY() + _firstWeapon->getH() + distanceBetweenEquipmentSlots);

		//Callbacks
	_firstWeapon->onDown([this](Game* game) { setDistanceWeapon(game); });
	_secondWeapon->onDown([this](Game* game) { setDistanceWeapon(game); });
	_meleeWeapon->onDown([this](Game* game) { setMeleeWeapon(game); });

		//Añadir como hijo
	addChild(_firstWeapon);
	addChild(_secondWeapon);
	addChild(_meleeWeapon);

	//----BOTON DE CAMBIO DE EQUIPAMIENTO----//

	_changeButton = new ButtonUI(game, game->getTexture("Button"), [this](Game* game) {changeEquipedGuns(game); }, { 0,1,2,3 });
	_changeButton->setSize(itemEquipWidth * 0.75, itemEquipHeight / 2); //POSIBLEMENTE PROVISIONAL
	_changeButton->setPosition(_equipmentFrame->getX() + _equipmentFrame->getW() / 2 - _changeButton->getW() / 2,
								_equipmentFrame->getY() + _equipmentFrame->getH() / 4 + distanceBetweenEquipmentSlots / 2 - _changeButton->getH() - distanceBetweenEquipmentSlots * 0.25);

		//Añadir como hijo
	addChild(_changeButton);

	//----ALMACEN----//
}

DepotPanel::~DepotPanel()
{
	for (auto item : _items)
		removeChild(item);
}

void DepotPanel::setItems(list<ShopItem*>& list)
{
	_items = list;

	int margin = 20; // PROBABLEMENTE PROVISIONAL TAMBIEN
	itemWidth = (_depotFrame->getW() - margin) / itemsPerRow;
	itemHeight = (_depotFrame->getH() - margin) / itemsPerCol;

	itemHeight < itemWidth ? itemSize = itemHeight : itemSize = itemWidth;

	for (auto it : _items)
	{
			it->setSize(itemSize, itemSize);

			it->onDown([this, it](Game* game) {	selectItem(game, it); });

			addChild(it);
	}

	reorderDepot();
}

void DepotPanel::reorderDepot()
{
	int xOffset = (_depotFrame->getW() - itemSize * itemsPerRow) / (itemsPerRow + 1);
	int yOffset = (_depotFrame->getH() - itemSize * itemsPerCol) / (itemsPerCol + 1);

	ShopItem* primItem = nullptr;

	auto it = _items.begin();
	int fil = 0;
	while (fil < itemsPerCol && it != _items.end())
	{
		int col = 0;
		while (it != _items.end() && col < itemsPerRow)
		{
			auto item = *it;
			auto info = item->getItemInfo();

			if (info._sold && !info._equiped)
			{
				item->setVisible(true);

				if (primItem == nullptr)
				{
					item->setPosition(_depotFrame->getX() + xOffset, _depotFrame->getY() + yOffset);
					primItem = item;
				}
				else
					item->setPosition(primItem->getX() + (primItem->getW() + xOffset) * col, primItem->getY() + (primItem->getH() + yOffset) * fil);

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

	auto firstWeaponInfo = _firstWeapon->getItemInfo();
	auto firstWeaponImage = _firstWeapon->getItemImage();

	_firstWeapon->setItemInfo(_secondWeapon->getItemInfo());
	_firstWeapon->setItemImage(_secondWeapon->getItemImage());

	_secondWeapon->setItemInfo(firstWeaponInfo);
	_secondWeapon->setItemImage(firstWeaponImage);
}

void DepotPanel::selectItem(Game * game, ShopItem* item)
{
	_selectedItem = item;
}

void DepotPanel::setDistanceWeapon(Game* game)
{
	if (_selectedItem != nullptr)
	{
		reorderDepot();
	}
}

void DepotPanel::setMeleeWeapon(Game* game)
{
	if (_selectedItem != nullptr)
	{
		reorderDepot();
	}
}
