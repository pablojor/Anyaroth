#include "ShopItem.h"
#include "Game.h"


ShopItem::ShopItem(Game* game, Texture* image, int xPos, int yPos, int arrayPos) : ButtonUI(game, image, 0, {0, 0, 1, 1, 1}, arrayPos)
{
	_weaponIcon = new ImageUI(game, image, xPos, yPos);
	setPosition(xPos, yPos);
}

ShopItem::~ShopItem()
{
	if (_weaponIcon != nullptr) delete _weaponIcon;
}

void ShopItem::render() const
{
	_weaponIcon->render();
	ButtonUI::render();
}

void ShopItem::select(bool b)
{
	_selected = b;

	if (_selected)
		setFrames({ 1, 1, 1, 1, 1 });
	else
		setFrames({ 0, 0, 1, 1, 1 });

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
	_info = info;

	//Frame (cambio al frame del color por rareza)
	setImage(_game->getTexture(_info._rarityFrame));
	//Cambio del icono del arma
	_weaponIcon->setImage(_game->getTexture(_info._iconName));
	//Ajustamos tamaños
	setSize(getImage()->getW(), getImage()->getH());
}

void ShopItem::setMeleeInfo(const MeleeItemInfo & info)
{
	_meleeInfo = info;

	//Frame (cambio al frame del color por rareza)
	setImage(_game->getTexture(_meleeInfo._rarityFrame));
	//Cambio del icono del arma
	_weaponIcon->setImage(_game->getTexture(_meleeInfo._iconName));
	//Ajustamos tamaños
	setSize(getImage()->getW(), getImage()->getH());
}

