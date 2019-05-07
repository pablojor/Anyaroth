#include "ShopEvent.h"

void ShopEvent::update(const double& time)
{
	if (_shop->isClosed())
		_finished = true;
}

void ShopEvent::play()
{
	_shop->openShop();
}