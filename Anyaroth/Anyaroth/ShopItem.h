#pragma once
#include "ButtonUI.h"
#include "TextUI.h"
#include "ImageUI.h"
#include "GunType_def.h"


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

struct MeleeItemInfo
{
	int _zone;

	string _name;

	int _damage;

	MeleeType _type;
	string _iconName;
	string _rarityFrame;

	bool _sold;
	bool _equiped;
};

class ShopItem : public ButtonUI
{
	private:
  
  ItemInfo _info;
  MeleeItemInfo _meleeInfo = {};
	ImageUI* _weaponIcon = nullptr;
  
public:
	ShopItem(Game* game, Texture* image = nullptr, int xPos = 0, int yPos = 0);
	~ShopItem();

	virtual void render() const;

	inline Texture* getItemImage() const { return getImage(); }
	inline ItemInfo& getItemInfo() { return _info; }
	inline void getItem(Game* game) {  }
  
	virtual void setPosition(int x, int y);
	virtual void setSize(int w, int h);
  
		inline Texture* getItemImage() const { return getImage(); }
		inline ItemInfo& getItemInfo() { return _info; }
		inline MeleeItemInfo& getMeleeInfo() { return _meleeInfo; }
		inline void getItem(Game* game) {  }
    
		void setItemImage(Texture* image) { setImage(image); }
		void setItemInfo(const ItemInfo& info);
		void setMeleeInfo(const MeleeItemInfo & info);

		void setItemSell(const bool& b) { _info._sold = b; }
		void setItemEquiped(const bool& b) { _info._equiped = b; }

		void setChosen(bool chosen);
		void setSelected(bool selected) { ButtonUI::setSelected(selected); setChosen(selected); }
};