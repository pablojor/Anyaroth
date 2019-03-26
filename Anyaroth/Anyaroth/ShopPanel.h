#pragma once
#include "PanelUI.h"
#include "ImageUI.h"
#include "ShopItem.h"
#include <list>

class ShopPanel : public PanelUI
{
private:
	ImageUI* _backGroundImage = nullptr;
	
	//Aun por implementar
	//ButtonUI* _rightButton = nullptr;
	//ButtonUI* _leftButton = nullptr;

	//Estos items serán los que se muestren en la tienda
	list<ShopItem*> _items;

	public:
		ShopPanel(Game* game);
		~ShopPanel();
};

