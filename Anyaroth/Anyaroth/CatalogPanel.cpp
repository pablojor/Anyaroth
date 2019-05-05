#include "CatalogPanel.h"
#include "Game.h"
#include "ShopMenu.h"
#include "Player.h"
#include "GameManager.h"

CatalogPanel::CatalogPanel(Game* game) : PanelUI(game)
{
	//----MARCO----//

	_frame = new ImageUI(game, game->getTexture("CatalogPanel"), 21, 5);

	addChild(_frame);

	//----BOTON DE SALIR----//

	_exitButton = new ButtonUI(game, game->getTexture("ReturnButton"), nullptr, { 0, 1, 1, 1, 1 });
	_exitButton->setPosition(CAMERA_RESOLUTION_X - _exitButton->getW() - 12, 188 - 1 - _exitButton->getH());

	addChild(_exitButton);

	//----PANEL DE INFORMACI�N----//

	int infoPanelPosX = _frame->getX() + _frame->getW() + 1,
		infoPanelPosY = _frame->getY() + 11;

	_infoPanel = new ShopInfoPanel(game, infoPanelPosX, infoPanelPosY);
	_infoPanel->setVisible(false);

	addChild(_infoPanel);

	//----BOTON DE COMPRAR----//

	_buyButton = new ButtonUI(game, game->getTexture("BuyButton"), nullptr, { 0, 1, 1, 1, 1 });
	_buyButton->setPosition(infoPanelPosX + _infoPanel->getInfoPanelWidth() / 2 - _buyButton->getW() / 2, infoPanelPosY + _infoPanel->getInfoPanelHeight() + 2);
	_buyButton->onDown([this](Game* game) { buyItem(game); });
	_buyButton->setVisible(false);


	_buyText = new TextUI(game, "Buy", game->getFont("ARIAL12"), 12, 0, 0, { 255, 255, 255, 255 });
	_buyText->setPosition(_buyButton->getX() + _buyButton->getW() / 2 - _buyText->getW() / 2,
							_buyButton->getY() + _buyButton->getH() / 2 - _buyText->getH() / 2);
	_buyText->setVisible(false);

	addChild(_buyButton);
	addChild(_buyText);

	//----MOSTRADOR DE DINERO----//

	_playerMoney = new CoinsCounter(game, CAMERA_RESOLUTION_X - 30, 3);

	addChild(_playerMoney);
}

bool CatalogPanel::handleEvent(const SDL_Event& event)
{
	if (_visible)
	{
		if (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			if (_buyButton->isVisible())
			{
				_infoPanel->closeInfoPanel();
				_buyButton->setVisible(false);
				_buyText->setVisible(false);
				_selectedButton = _selectedItem;
				_selectedButton->setSelected(true);
				_selectedItem->setChosen(false);
			}
			else
				_exitButton->callDown();
			return true;
		}
		else if (_game->usingJoystick() && event.type == SDL_MOUSEMOTION)
		{
			_selectedButton->setSelected(false);
			SDL_ShowCursor(true);
			_game->changeControlMode();
		}
	}
	return PanelUI::handleEvent(event);;
}

void CatalogPanel::inicializeCallbacks(ShopMenu* menu)
{
	_exitButton->onDown([menu](Game* game) {menu->closeCatalogPanel(game); });
}

void CatalogPanel::setPlayer(Player* ply)
{
	_player = ply;
}

void CatalogPanel::setItems(list<ShopItem*>* list) // Crear items
{
	_items = list;
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
	_playerMoney->updateCoinsCounter(_player->getBank());
	_zone = GameManager::getInstance()->getCurrentLevel();
	for (auto it : *_items)
			it->onDown([this, it](Game* game) {	selectItem(game, it); });

	reorderCatalog();

	setVisible(true);

	_infoPanel->setVisible(false);
	_buyButton->setVisible(false);
	_buyText->setVisible(false);
}

void CatalogPanel::closeCatalog()
{
	setVisible(false);

	_infoPanel->setVisible(false);
	_buyButton->setVisible(false);
	_buyText->setVisible(false);

	if (_selectedItem != nullptr)
	{
		_selectedItem->setChosen(false);
		_selectedItem = nullptr;
	}

	_selectedButton->setSelected(false);
	_selectedButton = nullptr;
}

void CatalogPanel::reorderCatalog()
{
	int posIniX = 11,
		posIniY = 10,
		distX = 9,
		distY = 4;

	ShopItem* primItem = nullptr;
	vector<ShopItem*> visibleItems;

	auto it = (*_items).begin();
	int fil = 0;
	while (fil < itemsPerCol && it != (*_items).end())
	{
		int col = 0;
		while (it != (*_items).end() && col < itemsPerRow)
		{
			auto item = *it;
			auto info = item->getItemInfo();

			if (!info._sold && info._zone <= _zone && info._zone != -1)
			{
				item->setVisible(true);
				visibleItems.push_back(item);

				if (primItem == nullptr)
				{
					item->setPosition(_frame->getX() + posIniX, _frame->getY() + posIniY);
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

	for (int i = 0; i < visibleItems.size(); i++)
	{
		ButtonUI* nL = (i > 0) ? visibleItems[i - 1] : _exitButton;
		ButtonUI* nU = (i > 1) ? visibleItems[i - 2] : _exitButton;
		ButtonUI* nR = (i + 1 < visibleItems.size()) ? visibleItems[i + 1] : _exitButton;
		ButtonUI* nD = (i + 2 < visibleItems.size()) ? visibleItems[i + 2] : _exitButton;
		visibleItems[i]->setNextButtons({ nL, nU, nR, nD });
	}
	
	if (visibleItems.size() > 0)
	{
		_selectedButton = *(visibleItems.begin());
		_exitButton->setNextButtons({ *prev(visibleItems.end()), *prev(visibleItems.end()), *(visibleItems.begin()), *(visibleItems.begin()) });
	}
	else
	{
		_selectedButton = _exitButton;
		_exitButton->setNextButtons({ nullptr, nullptr, nullptr, nullptr });
	}

	if (_game->usingJoystick())
		_selectedButton->setSelected(true);
}

void CatalogPanel::selectItem(Game * game, ShopItem* item)
{
	if (_selectedItem != nullptr)
		_selectedItem->setChosen(false);

	if (_game->isJoystick())
	{
		item->setSelected(false);
		_selectedButton = _buyButton;
		_selectedButton->setSelected(true);
	}
	_selectedItem = item;
	_selectedItem->setChosen(true);

	showSelectedItemInfo();
}

void CatalogPanel::showItemInfo(ShopItem* item)
{
	auto info = item->getItemInfo();
	_infoPanel->setName(info._name);
	_infoPanel->setCadence(info._cadence);
	_infoPanel->setDamage(info._damage);
	_infoPanel->setClip(info._clip);
	_infoPanel->setPrice(info._price);

	_infoPanel->openInfoPanel();

}

void CatalogPanel::showSelectedItemInfo() 
{
	if (_selectedItem != nullptr)
	{
		showItemInfo(_selectedItem);

		auto info = _selectedItem->getItemInfo();

		_buyButton->setVisible(true);
		_buyText->setVisible(true);

		if (info._price > _player->getBank())
		{
			_buyButton->setInputEnable(false);
			_buyText->setColor({ 55, 55, 55, 255 });
			_buyButton->setVisible(false);
			_buyText->setVisible(false);
		}
		else
		{
			_buyButton->setInputEnable(true);
			_buyText->setColor({ 255, 255, 255, 255 });
			_buyButton->setVisible(true);
			_buyText->setVisible(true);
			if (_game->usingJoystick())
			{
				_selectedButton->setSelected(false);
				_selectedItem->setChosen(true);
				_selectedButton = _buyButton;
				_selectedButton->setSelected(true);
			}
		}
	}
	else
		_infoPanel->closeInfoPanel();
}

void CatalogPanel::buyItem(Game * game)
{
	if (_player->spendMoney(_selectedItem->getItemInfo()._price))
	{
		_infoPanel->closeInfoPanel();
		_buyButton->setVisible(false);
		_buyText->setVisible(false);
		_selectedItem->setVisible(false);
		_selectedItem->setItemSell(true);

		_playerMoney->updateCoinsCounter(_player->getBank());



		_selectedItem->setChosen(false);
		_selectedItem = nullptr;


		reorderCatalog();
	}
}