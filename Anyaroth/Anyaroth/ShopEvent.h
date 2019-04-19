#pragma once
#include "Event.h"
#include "ShopMenu.h"

class ShopEvent : public Event
{
	private:
		ShopMenu* _shop;
	public:
		ShopEvent(ShopMenu* shop);

		virtual void update(const double& time);

		virtual void play();
};

