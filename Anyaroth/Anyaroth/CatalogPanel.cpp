#include "CatalogPanel.h"
#include "Game.h"
#include "ShopMenu.h"

ShopInfoPanel* CatalogPanel::_infoPanel = nullptr;
ButtonUI* CatalogPanel::_buyButton = nullptr;

CatalogPanel::CatalogPanel(Game* game) : PanelUI(game)
{
	//----MARCO----//

	_frame = new ImageUI(game, game->getTexture("ShopPanel"), 5, 5);

	addChild(_frame);

	//----BOTON DE SALIR----//

	_exitButton = new ButtonUI(game, game->getTexture("Button"), ShopMenu::closeCatalogPanel, { 0,1,2,3 });
	_exitButton->setPosition(_frame->getX(), _frame->getY() + _frame->getH() + 2);
	_exitButton->setSize(_frame->getW(), _exitButton->getH() + 4);

	addChild(_exitButton);

	//----PANEL DE INFORMACIÓN----//

	int infoPanelPosX = _frame->getX() + _frame->getW() + 4,
		infoPanelPosY = _frame->getY();

	_infoPanel = new ShopInfoPanel(game, infoPanelPosX, infoPanelPosY);
	_infoPanel->setVisible(false);

	addChild(_infoPanel);

	//----BOTON DE COMPRAR----//

	_buyButton = new ButtonUI(game, game->getTexture("BuyButton"), nullptr, { 0,1,2,1 });
	_buyButton->setPosition(infoPanelPosX + _infoPanel->getInfoPanelWidth() / 2 - _buyButton->getW() / 2, infoPanelPosY + _infoPanel->getInfoPanelHeight() + 2);
	_buyButton->onDown(buyItem);
	_buyButton->setVisible(false);

	addChild(_buyButton);
}

CatalogPanel::~CatalogPanel()
{
	for (auto item : _items)
		removeChild(item);
}

void CatalogPanel::setItems(list<ShopItem*>& list) // Crear items
{
	_items = list;

	itemWidth = (_frame->getW() - 10) / itemsPerRow;
	itemHeight = (_frame->getH() - 10) / itemsPerCol;

	itemHeight < itemWidth ? itemSize = itemHeight : itemSize = itemWidth;

	for (auto it : _items)
	{
		it->onDown(selectItem);
		it->setSize(itemSize, itemSize);
		it->setVisible(false);

		addChild(it);
	}
}

void CatalogPanel::openCatalog()
{
	_visible = true;
	_infoPanel->setVisible(false);
	_buyButton->setVisible(false);
}

void CatalogPanel::updateCatalog(int zona) // Colocar items
{
	int xOffset = (_frame->getW() - itemSize * itemsPerRow) / (itemsPerRow + 1);
	int yOffset = (_frame->getH() - itemSize * itemsPerCol) / (itemsPerCol + 1);

	ShopItem* primItem = nullptr;

	auto it = _items.begin();
	int fil = 0;
	while (fil < itemsPerCol && it != _items.end())
	{
		int col = 0;
		while (it != _items.end() && col < itemsPerRow)
		{
			auto item = *it;

			if (!item->getItemInfo()._sell && item->getItemInfo()._zona <= zona && item->getItemInfo()._zona != -1)
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

			it++;
		}

		fil++;
	}
}

void CatalogPanel::selectItem(Game * game)
{
	_infoPanel->setVisible(true);
	_buyButton->setVisible(true);

	_infoPanel->setName("Gun");
}

void CatalogPanel::buyItem(Game * game)
{
	cout << "comprado" << endl;

	_infoPanel->setVisible(false);
	_buyButton->setVisible(false);
	/*_selectedItem->setVisible(false);
	_selectedItem->setItemSell(true);*/
}
