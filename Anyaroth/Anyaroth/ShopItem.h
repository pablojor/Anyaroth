#pragma once
#include "ButtonUI.h"
#include "TextUI.h"

class ShopItem : public ButtonUI
{
	private:
		struct ItemInfo 
		{
			int _zona;

			string _name;
			int _damage;
			int _cadence;
			int _distance;

			bool _sell;
			bool _equiped;
		};

		ItemInfo _info;
		static ShopItem* _selected;

	public:
		ShopItem(Game* game, Texture* image = nullptr, int xPos = 0, int yPos = 0);
		~ShopItem();

		inline Texture* getItemImage() const { return getImage(); }
		inline ItemInfo getItemInfo() const { return _info; }
		static inline void getItem(Game* game) {  }

		void setItemImage(Texture* image) { setImage(image); }
		void setItemInfo(const ItemInfo& info) { _info = info; }

		void setItemSell(bool b) { _info._sell = b; }
		void setItemEquiped(bool b) { _info._equiped = b; }
};

