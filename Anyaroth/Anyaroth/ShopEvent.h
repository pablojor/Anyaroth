#pragma once
#include "Event.h"
#include "ShopMenu.h"

class ShopEvent : public Event
{
	private:
		int _currentZone;
		ShopMenu* _shop;
	public:
		ShopEvent(ShopMenu* shop, int currentZone);

		virtual void update(const double& time);

		virtual void play();
};

