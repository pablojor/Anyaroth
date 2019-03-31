#pragma once
#include "ButtonUI.h"
#include "TextUI.h"

class ShopItem : public ButtonUI
{
	private:
		struct ItemInfo 
		{
			string _name;
			string _damage;
			string _cadence;
			string _distance;

			bool _available;
			bool _sell;
		};

		ItemInfo _info;

	public:
		ShopItem(Game* game, Texture* image = nullptr, int xPos = 0, int yPos = 0);
		~ShopItem();

		inline Texture* getItemImage() const { getImage(); }
		inline ItemInfo getItemInfo() const { return _info; }

		void setItemImage(Texture* image) { setImage(image); }
		void setItemInfo(const ItemInfo& info) { _info = info; }
};

