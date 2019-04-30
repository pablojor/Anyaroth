#pragma once
#include "ButtonUI.h"
#include "TextUI.h"
#include "ImageUI.h"
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
			string _iconName;
			string _rarityFrame;

			bool _sold;
			bool _equiped;
		};

		ItemInfo _info;

		ImageUI* _weaponIcon = nullptr;

		bool _selected = false;


	public:
		ShopItem(Game* game, Texture* image = nullptr, int xPos = 0, int yPos = 0, int arrayPos = 0);
		~ShopItem();

		virtual void render() const;

		void select(bool b);

		inline Texture* getItemImage() const { return getImage(); }
		inline ItemInfo& getItemInfo() { return _info; }
		inline void getItem(Game* game) {  }

		virtual void setPosition(int x, int y);
		virtual void setSize(int w, int h);

		void setItemImage(Texture* image) { setImage(image); }
		void setItemInfo(const ItemInfo& info);

		void setItemSell(const bool& b) { _info._sold = b; }
		void setItemEquiped(const bool& b) { _info._equiped = b; }

		void setSelected(bool selected) { ButtonUI::setSelected(selected); select(selected); }
};

