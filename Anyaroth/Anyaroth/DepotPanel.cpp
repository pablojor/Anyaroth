#include "DepotPanel.h"
#include "Player.h"
#include "ShopMenu.h"
#include <functional>
#include <algorithm>
#include "Game.h"
#include "WeaponManager.h"
#include "GameManager.h"


DepotPanel::DepotPanel(Game* game) : PanelUI(game)
{
	//----MARCOS----//

	_depotFrame = new ImageUI(game, game->getTexture("DepotPanel"), 21, 29);
	_depotFrame->setSize(_depotFrame->getW(), 2 * _depotFrame->getH() / 3 + 3);
	_depotMeleeFrame = new ImageUI(game, game->getTexture("DepotPanel"), 21, _depotFrame->getY() + _depotFrame->getH() + 2);
	_depotMeleeFrame->setSize(3 * _depotFrame->getW() / 4, _depotMeleeFrame->getH() / 3 + 5);
	_depotMeleeFrame->setPosition(21 + _depotFrame->getW() / 2 - _depotMeleeFrame->getW() / 2, _depotMeleeFrame->getY());
	_equipmentFrame = new ImageUI(game, game->getTexture("EquipPanel"), _depotFrame->getX() + _depotFrame->getW() + 5, _depotFrame->getY() + 14);

	_depotFrameName = new FramedImageUI(game, game->getTexture("Equip/Depot_PanelName"));
	_depotFrameName->setPosition(_depotFrame->getX() + _depotFrame->getW() / 2 - _depotFrameName->getW() / 2, _depotFrame->getY() - 20);
	_equipmentFrameName = new FramedImageUI(game, game->getTexture("Equip/Depot_PanelName"));
	_equipmentFrameName->setPosition(_equipmentFrame->getX() + _equipmentFrame->getW() / 2 - _equipmentFrameName->getW() / 2, _equipmentFrame->getY() - 20);

	_depotName = new TextUI(game, "Storage", game->getFont("ARIAL12"), 12, 0, 0, { 145, 255, 255, 255 });
	_depotName->setPosition(_depotFrameName->getX() + _depotFrameName->getW() / 2 - _depotName->getW() / 2, _depotFrameName->getY() + _depotFrameName->getH() / 2 - _depotName->getH() / 2);
	
	_equipName = new TextUI(game, "Equipped", game->getFont("ARIAL12"), 12, 0, 0, { 145, 255, 255, 255 });
	_equipName->setPosition(_equipmentFrameName->getX() + _equipmentFrameName->getW() / 2 - _equipName->getW() / 2, _equipmentFrameName->getY() + _equipmentFrameName->getH() / 2 - _equipName->getH() / 2);

	//A�adir como hijo
	addChild(_depotFrame);
	addChild(_depotMeleeFrame);
	addChild(_equipmentFrame);

	addChild(_depotFrameName);
	addChild(_equipmentFrameName);

	addChild(_equipName);
	addChild(_depotName);

	//----BOTON DE SALIR----//

	_exitButton = new ButtonUI(game, game->getTexture("ReturnButton"), nullptr, { 0,1,1,1 });
	_exitButton->setPosition(CAMERA_RESOLUTION_X - _exitButton->getW() - 12, 188 - 1 - _exitButton->getH());

	_voidItem = new ShopItem(game, game->getTexture("VoidIcon"));
	_voidItem->setItemInfo(_voidItem->getItemInfo());
	_voidItem->setFrames({ 0, 0, 0, 0, 0 });

		//A�adir como hijo
	addChild(_exitButton);

	_firstWeaponFrame = new ShopItem(game, game->getTexture("VoidIcon"));
	_firstWeaponFrame->setPosition(_equipmentFrame->getX() + 8,	_equipmentFrame->getY() + 8);
	_firstWeaponFrame->setItemInfo(_firstWeaponFrame->getItemInfo());
	_firstWeaponFrame->setFrames({ 0, 0, 0, 0, 0 });

	_secondWeaponFrame = new ShopItem(game, game->getTexture("VoidIcon"));
	_secondWeaponFrame->setPosition(_firstWeaponFrame->getX() + _firstWeaponFrame->getW() + 26,	_firstWeaponFrame->getY());
	_secondWeaponFrame->setItemInfo(_secondWeaponFrame->getItemInfo());
	_secondWeaponFrame->setFrames({ 0, 0, 0, 0, 0 });
	//----EQUIPAMIENTO----//

	_meleeWeaponFrame = new ShopItem(game, game->getTexture("VoidIcon"));
	_meleeWeaponFrame->setItemInfo(_meleeWeaponFrame->getItemInfo());
	_meleeWeaponFrame->setPosition(_equipmentFrame->getX() + _equipmentFrame->getW() / 2 - _meleeWeaponFrame->getW() / 2,	_firstWeaponFrame->getY() + _firstWeaponFrame->getH() + distanceBetweenEquipmentSlots);
	_meleeWeaponFrame->setFrames({ 0, 0, 0, 0, 0 });

		//Callbacks
	_firstWeaponFrame->onDown([this](Game* game) { setDistanceWeapon(game, _firstWeaponFrame); });
	_secondWeaponFrame->onDown([this](Game* game) { setDistanceWeapon(game, _secondWeaponFrame); });
	_meleeWeaponFrame->onDown([this](Game* game) { setMeleeWeapon(game, _meleeWeaponFrame); });

	//----BOTON DE CAMBIO DE EQUIPAMIENTO----//

	_changeButton = new ButtonUI(game, game->getTexture("ChangeButton"), [this](Game* game) {changeEquipedGuns(game); }, { 0,1,1,1 });
	_changeButton->setPosition(_equipmentFrame->getX() + 45,
								_equipmentFrame->getY() + 17);

		//A�adir como hijo
	addChild(_changeButton);

	//----ALMACEN----//
}

bool DepotPanel::handleEvent(const SDL_Event& event)
{
	if (_visible)
	{
		if (event.type == SDL_CONTROLLERBUTTONDOWN && event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
		{
			if (_firstWeaponFrame->isSelected() || _secondWeaponFrame->isSelected() || _meleeWeaponFrame->isSelected())
			{
				_selectedItem->setChosen(false);
				_selectedButton->setSelected(false);
				_selectedButton = _selectedItem;
				_selectedButton->setSelected(true);
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

void DepotPanel::inicializeCallback(ShopMenu * menu)
{
	_exitButton->onDown([menu](Game* game) { menu->closeDepotPanel(game); });
}

void DepotPanel::setPlayer(Player * ply)
{
	_player = ply;

	ShopItem* fItem = nullptr, *sItem = nullptr, *mItem = nullptr;

	for (auto i = _weaponItems->begin(); i != _weaponItems->end(); i++)
	{
		if (_player->getCurrentGun() != nullptr && (*i)->getItemInfo()._type == _player->getCurrentGun()->getGunID() && !(*i)->getItemInfo()._isMelee)
			fItem = (*i);
		else if (_player->getOtherGun() != nullptr && (*i)->getItemInfo()._type == _player->getOtherGun()->getGunID() && !(*i)->getItemInfo()._isMelee)
			sItem = (*i);
	}

	for (auto i = _meleeItems->begin(); i != _meleeItems->end(); i++)
	{
		if ((*i)->getItemInfo()._type == _player->getMelee()->getMeleeID() && (*i)->getItemInfo()._isMelee)
			mItem = (*i);
	}

	ItemInfo* fInfo = nullptr, *sInfo = nullptr, *mInfo = nullptr;
	if (fItem == nullptr) 
		fItem = _voidItem;
	fInfo = &fItem->getItemInfo(); fInfo->_sold = true; fInfo->_equiped = true;

	if (sItem == nullptr) 
		sItem = _voidItem;
	sInfo = &sItem->getItemInfo(); sInfo->_sold = true; sInfo->_equiped = true;

	if (mItem == nullptr) 
		mItem = _voidItem;
	mInfo = &mItem->getItemInfo(); mInfo->_sold = true; mInfo->_equiped = true;

	_firstWeaponItem = fItem;
	_secondWeaponItem = sItem;
	_meleeWeaponItem = mItem;

	_firstWeaponFrame->setItemInfo(*fInfo);
	_secondWeaponFrame->setItemInfo(*sInfo);
	_meleeWeaponFrame->setItemInfo(*mInfo);

	addChild(_firstWeaponFrame);
	addChild(_secondWeaponFrame);
	addChild(_meleeWeaponFrame);
}

void DepotPanel::setWeaponItems(list<ShopItem*>* list)
{
	_weaponItems = list;
	for (auto it : *_weaponItems)
		addChild(it);
}

void DepotPanel::removeWeaponItems()
{
	for (auto it : *_weaponItems)
		removeChild(it);
}

void DepotPanel::setMeleeItems(list<ShopItem*>* list)
{
	_meleeItems = list;
	for (auto it : *_meleeItems)
		addChild(it);
}

void DepotPanel::removeMeleeItems()
{
	for (auto it : *_meleeItems)
		removeChild(it);
}

void DepotPanel::openDepotPanel()
{
	checkPlayer();

	for (auto it : *_weaponItems)
		it->onDown([this, it](Game* game) {	selectItem(game, it); });

	for(auto it : *_meleeItems)
		it->onDown([this, it](Game* game) {	selectItem(game, it); });

	reorderDepot();
	setVisible(true);

	if (_game->usingJoystick())
	{
		_selectedButton->setSelected(true);
		SDL_ShowCursor(false);
		SDL_WarpMouseGlobal(0, 0);
	}
}

void DepotPanel::closeDepotPanel()
{
	setVisible(false);

	if (_selectedItem != nullptr)
	{
		_selectedItem->setSelected(false);
		_selectedItem = nullptr;
	}

	_selectedButton->setSelected(false);
	_selectedButton = nullptr;
}

void DepotPanel::reorderDepot()
{
	//Armas a distancia
	int posIniX = 11,
		posIniY = 7,
		distX = 9,
		distY = 4;

	ShopItem* primItem = nullptr;
	vector<ShopItem*> visibleWeapons;
	vector<ShopItem*> visibleMelee;

	auto it = (*_weaponItems).begin();
	int fil = 0;


	while (fil < itemsPerCol && it != (*_weaponItems).end())
	{
		int col = 0;
		while (it != (*_weaponItems).end() && col < itemsPerRow)
		{
			auto item = *it;
			auto info = item->getItemInfo();

			if (info._sold && !info._equiped && info._type != None)
			{
				item->setVisible(true);
				visibleWeapons.push_back(item);

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

	//Armas melee
	primItem = nullptr;
	it = (*_meleeItems).begin();
	fil = 0;

	while (fil < itemsPerCol && it != (*_meleeItems).end())
	{
		int col = 0;
		while (it != (*_meleeItems).end() && col < itemsPerRow)
		{
			auto item = *it;
			auto info = item->getItemInfo();

			if (info._zone <= GameManager::getInstance()->getCurrentLevel() && !info._equiped)
			{
				item->setVisible(true);
				visibleMelee.push_back(item);

				if (primItem == nullptr)
				{
					item->setPosition(_depotMeleeFrame->getX() + posIniX, _depotMeleeFrame->getY() + posIniY);
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

	for (int i=0; i < visibleWeapons.size(); i++)
	{
		ButtonUI* nL = (i > 0) ? visibleWeapons[i - 1] : _exitButton;
		ButtonUI* nU = (i > 3) ? visibleWeapons[i - 4] : ((visibleMelee.begin() != visibleMelee.end()) ? *prev(visibleMelee.end()) : nullptr);
		ButtonUI* nR = (i + 1 < visibleWeapons.size()) ? visibleWeapons[i + 1] : _changeButton;
		ButtonUI* nD = (i + 4 < visibleWeapons.size()) ? visibleWeapons[i + 4] :((visibleMelee.begin() != visibleMelee.end()) ? *visibleMelee.begin() : nullptr);
		visibleWeapons[i]->setNextButtons({ nL, nU, nR, nD });
	}
	for (int i = 0; i < visibleMelee.size(); i++)
	{
		ButtonUI* nL = (i > 0) ? visibleMelee[i - 1] : _exitButton;
		ButtonUI* nU = (i > 3) ? visibleMelee[i - 4] : ((visibleWeapons.begin() != visibleWeapons.end()) ? *prev(visibleWeapons.end()) : nullptr);
		ButtonUI* nR = (i + 1 < visibleMelee.size()) ? visibleMelee[i + 1] : _changeButton;
		ButtonUI* nD = (i + 4 < visibleMelee.size()) ? visibleMelee[i + 4] : ((visibleWeapons.begin() != visibleWeapons.end()) ? *visibleWeapons.begin() : nullptr);
		visibleMelee[i]->setNextButtons({ nL, nU, nR, nD });
	}
	if (visibleWeapons.size() > 0)
	{
		_selectedButton = *(visibleWeapons.begin());

		_exitButton->setNextButtons({ _changeButton, nullptr, *(visibleWeapons.begin()), nullptr });
		_changeButton->setNextButtons({ *prev(visibleWeapons.end()), nullptr, _exitButton, nullptr });
	}
	else if (visibleMelee.size() > 0)
	{
		_selectedButton = *(visibleMelee.begin());

		_exitButton->setNextButtons({ _changeButton, nullptr, *(visibleMelee.begin()), nullptr });
		_changeButton->setNextButtons({ *prev(visibleMelee.end()), nullptr, _exitButton, nullptr });
	}
	else
	{
		_selectedButton =  _changeButton;

		_exitButton->setNextButtons({ _changeButton, nullptr, _changeButton, nullptr });
		_changeButton->setNextButtons({ _exitButton, nullptr, _exitButton, nullptr });
	}

	_meleeWeaponFrame->setNextButtons({ nullptr, nullptr, nullptr, nullptr });
	_firstWeaponFrame->setNextButtons({ _secondWeaponFrame, nullptr, _secondWeaponFrame, nullptr });
	_secondWeaponFrame->setNextButtons({ _firstWeaponFrame, nullptr, _firstWeaponFrame, nullptr });

	if (_game->usingJoystick())
		_selectedButton->setSelected(true);
}

void DepotPanel::changeEquipedGuns(Game* game)
{
	if (_secondWeaponFrame->getItemInfo()._type != None)
	{
		_player->swapGun();

		auto firstWeaponInfo = _firstWeaponFrame->getItemInfo();
		_firstWeaponFrame->setItemInfo(_secondWeaponFrame->getItemInfo());

		_secondWeaponFrame->setItemInfo(firstWeaponInfo);

		auto aux = _firstWeaponItem;
		_firstWeaponItem = _secondWeaponItem;
		_secondWeaponItem = aux;
	}
}

void DepotPanel::selectItem(Game * game, ShopItem* item)
{
	if (_selectedItem != nullptr)
	{
		_selectedItem->setChosen(false);

		if (_selectedItem != item)
		{
			if (_game->usingJoystick())
			{
				_selectedButton->setSelected(false);				
				_selectedButton = (item->getItemInfo()._isMelee) ? _meleeWeaponFrame : _firstWeaponFrame;
				_selectedButton->setSelected(true);
			}
			_selectedItem = item;
			_selectedItem->setChosen(true);
		}
		else
			_selectedItem = nullptr;
	}
	else if (item != _firstWeaponFrame && item != _secondWeaponFrame && item != _meleeWeaponFrame)
	{
		if (_game->usingJoystick())
		{
			_selectedButton->setSelected(false);
			_selectedButton = (item->getItemInfo()._isMelee) ? _meleeWeaponFrame : _firstWeaponFrame;
			_selectedButton->setSelected(true);
		}
		_selectedItem = item;
		_selectedItem->setChosen(true);
	}
}

void DepotPanel::setDistanceWeapon(Game* game, ShopItem* item)
{
	if (_selectedItem != nullptr && !_selectedItem->getItemInfo()._isMelee) //COMPROBAR QUE NO ES MELEE
	{
		swapDistanceItems(item);
		reorderDepot();

		_selectedItem->setChosen(false);
		_selectedItem = nullptr;
	}
}

void DepotPanel::setMeleeWeapon(Game* game, ShopItem* item)
{
	if (_selectedItem != nullptr && _selectedItem->getItemInfo()._isMelee) //COMPROBAR QUE NO ES A DISTANCIA
	{
		swapMeleeItems(item);
		_meleeWeaponFrame->setSelected(false);
		reorderDepot();

		_selectedItem->setChosen(false);
		_selectedItem = nullptr;
	}
}

void DepotPanel::swapDistanceItems(ShopItem* _equiped)
{
	//Cambiamos la info
	auto infoSelected = _selectedItem->getItemInfo();
	auto infoEquiped = _equiped->getItemInfo();
	infoSelected._equiped = true;
	infoEquiped._equiped = false;

	_equiped->setSelected(false);

	if (infoEquiped._name == _firstWeaponFrame->getItemInfo()._name)
		_firstWeaponItem->setItemInfo(infoSelected);
	else
		_secondWeaponItem->setItemInfo(infoSelected);

	if (infoEquiped._type != None)
		_selectedItem->setItemInfo(infoEquiped);
	else
		_selectedItem->setItemEquiped(true);
	_equiped->setItemInfo(infoSelected);

	//Equipo arma
	Gun* newGun = WeaponManager::getInstance()->getWeapon(_game, (GunType)_equiped->getItemInfo()._type);
	if (_equiped == _firstWeaponFrame) 
		_player->changeCurrentGun(newGun);
	else if (_equiped == _secondWeaponFrame)
		_player->changeOtherGun(newGun);
}

void DepotPanel::swapMeleeItems(ShopItem* _equiped)
{
	//Cambiamos la info
	auto infoSelected = _selectedItem->getItemInfo();
	auto otherInfo = _equiped->getItemInfo();
	infoSelected._equiped = true;
	otherInfo._equiped = false;

	_selectedItem->setItemInfo(otherInfo);
	_equiped->setItemInfo(infoSelected);

	MeleeType type = (MeleeType)_equiped->getItemInfo()._type;
	Melee* newMelee = WeaponManager::getInstance()->getMelee(_game, type);
	//FALTA EQUIPAR EL ARMA
	int anim = AnimatedSpriteComponent::MeleeKnife;
	if (type == Sword_Weapon) anim = AnimatedSpriteComponent::MeleeSword;
	else if (type == PoleAxe_Weapon) anim = AnimatedSpriteComponent::MeleeHalberd;

	_player->changeMelee(newMelee, anim);
}


void DepotPanel::checkPlayer()
{
	if (_firstWeaponFrame->getItemInfo()._type != _player->getCurrentGun()->getGunID())
	{
		auto firstWeaponInfo = _firstWeaponFrame->getItemInfo();
		_firstWeaponFrame->setItemInfo(_secondWeaponFrame->getItemInfo());

		_secondWeaponFrame->setItemInfo(firstWeaponInfo);

		auto aux = _firstWeaponItem;
		_firstWeaponItem = _secondWeaponItem;
		_secondWeaponItem = aux;
	}
}