#include "ShopItem.h"
#include "Game.h"

ShopItem::ShopItem(Game* game, Texture* image, int xPos, int yPos) : ButtonUI(game, image, 0, {0, 2, 2, 2, 2})
{
	_weaponIcon = new ImageUI(game, image, xPos, yPos);
	setPosition(xPos, yPos);
	setImage(game->getTexture("ItemFrame"));
}

ShopItem::~ShopItem()
{
	if (_weaponIcon != nullptr) delete _weaponIcon;
}

void ShopItem::render() const
{
	if (_weaponIcon->getImage() != nullptr) _weaponIcon->render();
	ButtonUI::render();
}

void ShopItem::setPosition(int x, int y)
{
	ButtonUI::setPosition(x, y);
	_weaponIcon->setPosition(x, y);
}

void ShopItem::setSize(int w, int h)
{
	auto fils = getImage()->getNumFils();
	auto cols = getImage()->getNumCols();
	ButtonUI::setSize(w / cols, h / fils);
	_weaponIcon->setSize(w / cols, h / fils);
}

void ShopItem::setItemInfo(const ItemInfo & info)
{
	if (&info != nullptr) {
		_info = info;

		//Frame (cambio al frame del color por rareza)
		setImage(_game->getTexture(_info._rarityFrame));
		//Cambio del icono del arma
		_weaponIcon->setImage(_game->getTexture(_info._iconName));
		//Ajustamos tama�os
		setSize(getImage()->getW(), getImage()->getH());
	}
}

void ShopItem::setChosen(bool selected)
{
	if (selected && !_game->usingJoystick())
		setFrames({ 1, 2, 1, 1, 1 });
	else if(selected && _game->usingJoystick())
		setFrames({ 1, 2, 1, 1, 1 });
	else
		setFrames({ 0, 2, 2, 2, 2 });
}