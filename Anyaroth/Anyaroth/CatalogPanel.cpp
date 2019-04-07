#include "CatalogPanel.h"
#include "Game.h"
#include "ShopMenu.h"
#include "Player.h"

CatalogPanel::CatalogPanel(Game* game) : PanelUI(game)
{
	//----MARCO----//

	_frame = new ImageUI(game, game->getTexture("CatalogPanel"), 21, 5);

	addChild(_frame);

	//----BOTON DE SALIR----//

	_exitButton = new ButtonUI(game, game->getTexture("ReturnButton"), nullptr, { 0,1,1,1 });
	_exitButton->setPosition(CAMERA_RESOLUTION_X - _exitButton->getW() - 12, 188 - 1 - _exitButton->getH());

	addChild(_exitButton);

	//----PANEL DE INFORMACIÓN----//

	int infoPanelPosX = _frame->getX() + _frame->getW() + 1,
		infoPanelPosY = _frame->getY() + 17;

	_infoPanel = new ShopInfoPanel(game, infoPanelPosX, infoPanelPosY);
	_infoPanel->setVisible(false);

	addChild(_infoPanel);

	//----BOTON DE COMPRAR----//

	_buyButton = new ButtonUI(game, game->getTexture("BuyButton"), nullptr, { 0,1,1,1 });
	_buyButton->setPosition(infoPanelPosX + _infoPanel->getInfoPanelWidth() / 2 - _buyButton->getW() / 2, infoPanelPosY + _infoPanel->getInfoPanelHeight() + 2);
	_buyButton->onDown([this](Game* game) { buyItem(game); });
	_buyButton->setVisible(false);

	addChild(_buyButton);

	//----MOSTRADOR DE DINERO----//

	_playerMoney = new CoinsCounter(game, CAMERA_RESOLUTION_X - 30, 3);

	addChild(_playerMoney);
}


void CatalogPanel::inicializeCallbacks(ShopMenu* menu)
{
	_exitButton->onDown([menu](Game* game) {menu->closeCatalogPanel(game); });
}

void CatalogPanel::setPlayer(Player* ply)
{
	_player = ply;

	_playerMoney->updateCoinsCounter(_player->getBank());
}

void CatalogPanel::setItems(list<ShopItem*>* list, const int& zone) // Crear items
{
	_items = list;
	_zone = zone;

	int margin = 20; // PROBABLEMENTE PROVISIONAL TAMBIEN
	itemWidth = (_frame->getW() - margin) / itemsPerRow;
	itemHeight = (_frame->getH() - margin) / itemsPerCol;

	itemHeight < itemWidth ? itemSize = itemHeight : itemSize = itemWidth;

	for (auto it : *_items)
		addChild(it);
}

void CatalogPanel::removeItems()
{
	for (auto it : *_items)
		removeChild(it);
}

void CatalogPanel::openCatalog()
{
	for (auto it : *_items)
	{
		it->onDown([this, it](Game* game) {	selectItem(game, it); });
		//it->onOver([this, it](Game* game) { showItemInfo(it); });
		//it->onOut([this, it](Game* game) { showSelectedItemInfo(); });
		it->setSize(itemSize, itemSize);
	}
	reorderCatalog();

	_visible = true;
	_infoPanel->setVisible(false);
	_buyButton->setVisible(false);
}

void CatalogPanel::closeCatalog()
{
	setVisible(false);
	_infoPanel->setVisible(false);
	_buyButton->setVisible(false);
	_selectedItem = nullptr;
}

void CatalogPanel::reorderCatalog()
{
	int xOffset = (_frame->getW() - itemSize * itemsPerRow) / (itemsPerRow + 1);
	int yOffset = (_frame->getH() - itemSize * itemsPerCol) / (itemsPerCol + 1);

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

			if (!info._sold && info._zona <= _zone && info._zona != -1)
			{
				item->setVisible(true);
				if (primItem == nullptr)
				{
					item->setPosition(_frame->getX() + xOffset, _frame->getY() + yOffset);
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

void CatalogPanel::selectItem(Game * game, ShopItem* item)
{
	_selectedItem = item;

	showSelectedItemInfo();
}

void CatalogPanel::showItemInfo(ShopItem* item)
{
	auto info = item->getItemInfo();
	_infoPanel->setName(info._name);
	_infoPanel->setCadence(info._cadence);
	_infoPanel->setDamage(info._damage);
	_infoPanel->setDistance(info._distance);
	_infoPanel->setPrice(info._price);
	_infoPanel->setVisible(true);	

	if (item == _selectedItem) 
		_buyButton->setVisible(true);
	else
		_buyButton->setVisible(false);
}

void CatalogPanel::showSelectedItemInfo() 
{
	if (_selectedItem != nullptr)
	{
		showItemInfo(_selectedItem);

		auto info = _selectedItem->getItemInfo();

		_buyButton->setVisible(true);
		if (info._price > _player->getBank())
			_buyButton->setInputEnable(false);
		else
			_buyButton->setInputEnable(true);
	}
	else
		_infoPanel->setVisible(false);
}

void CatalogPanel::buyItem(Game * game)
{
	if (_player->spendMoney(_selectedItem->getItemInfo()._price))
	{
		_infoPanel->setVisible(false);
		_buyButton->setVisible(false);
		_selectedItem->setVisible(false);
		_selectedItem->setItemSell(true);

		_playerMoney->updateCoinsCounter(_player->getBank());
		_selectedItem = nullptr;

		reorderCatalog();
	}
}

