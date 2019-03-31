#include "CatalogPanel.h"
#include "Game.h"
#include "ShopMenu.h"

CatalogPanel::CatalogPanel(Game* game) : PanelUI(game)
{
	_frame = new ImageUI(game, game->getTexture("ShopPanel"), 5, 5);

	_exitButton = new ButtonUI(game, game->getTexture("Button"), ShopMenu::closeCatalogPanel, { 0,1,2,3 });
	_exitButton->setPosition(_frame->getX(), _frame->getY() + _frame->getH() + 2);
	_exitButton->setSize(_frame->getW(), _exitButton->getH() + 4);

	_infoPanel = new ShopInfoPanel(game, _frame->getX() + _frame->getW() + 4, _frame->getY());

	addChild(_frame);
	addChild(_exitButton);
	addChild(_infoPanel);	
}

CatalogPanel::~CatalogPanel()
{
	for (auto item : _items)
		removeChild(item);
}

void CatalogPanel::setItems(list<ShopItem*>& list)
{
	_items = list;

	//Creacion de items
	int itemsPerRow = 2;
	int itemsPerCol = 4;
	int itemWidth = (_frame->getW() - 10) / itemsPerRow;
	int itemHeight = (_frame->getH() - 10) / itemsPerCol;
	int itemSize;
	itemHeight < itemWidth ? itemSize = itemHeight : itemSize = itemWidth;
	int xOffset = (_frame->getW() - itemSize * itemsPerRow) / (itemsPerRow + 1);
	int yOffset = (_frame->getH() - itemSize * itemsPerCol) / (itemsPerCol + 1);
	ShopItem* primItem = nullptr;

	auto it = _items.begin();
	for (int j = 0; j < itemsPerCol && it != _items.end(); j++)
	{
		for (int i = 0; i < itemsPerRow && it != _items.end(); i++)
		{
			auto item = *it;
			item->setSize(itemSize, itemSize);
			if (primItem == nullptr)
				item->setPosition(_frame->getX() + xOffset, _frame->getY() + yOffset);
			else
				item->setPosition(primItem->getX() + (primItem->getW() + xOffset) * i, primItem->getY() + (primItem->getH() + yOffset) * j);
			_items.push_back(item);
			addChild(item);
			if (primItem == nullptr) primItem = item;
			it++;
		}
	}
}
