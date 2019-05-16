#pragma once
#include "Event.h"
#include "ShopMenu.h"

class ShopEvent : public Event
{
private:
	ShopMenu* _shop;

public:
	ShopEvent(ShopMenu* shop) : _shop(shop) {}
	virtual ~ShopEvent() {};

	virtual void update(double time);
	virtual void play();
};