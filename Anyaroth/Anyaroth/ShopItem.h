#pragma once
#include "ButtonUI.h"
#include "TextUI.h"
#include "GunType_def.h"

class ShopItem : public ButtonUI
{
	private:
		struct ItemInfo 
		{
			int _zone;

			string _name;
			int _price;

			int _damage;
			int _cadence;
			int _clip;

			//ID del arma
			GunType _type;

			bool _sold;
			bool _equiped;
		};

		ItemInfo _info;

	public:
		ShopItem(Game* game, Texture* image = nullptr, int xPos = 0, int yPos = 0);
		~ShopItem();

		inline Texture* getItemImage() const { return getImage(); }
		inline ItemInfo& getItemInfo() { return _info; }
		inline void getItem(Game* game) {  }

		void setItemImage(Texture* image) { setImage(image); }
		void setItemInfo(const ItemInfo& info) { _info = info; }

		void setItemSell(bool b) { _info._sold = b; }
		void setItemEquiped(bool b) { _info._equiped = b; }
};

