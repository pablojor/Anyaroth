#pragma once
#include "ButtonUI.h"
#include "TextUI.h"
#include "ImageUI.h"
#include "GunType_def.h"

struct ItemInfo
{
	int _zone = -100;

	string _name = "NoWeapon";
	int _price = 0;

	int _damage = 0;
	int _cadence = 0;
	int _clip = 0;

	//ID del arma
	uint _type = 100;
	string _iconName = "VoidIcon";
	string _rarityFrame = "ItemFrame";

	bool _sold = false;
	bool _equiped = false;

	bool _isMelee = false;
};

class ShopItem : public ButtonUI
{
private:
	ItemInfo _info;
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

	void setItemImage(Texture* image) { setImage(image); }
	void setItemInfo(const ItemInfo& info);

	void setItemSell(bool b) { _info._sold = b; }
	void setItemEquiped(bool b) { _info._equiped = b; }

	void setChosen(bool chosen);
	void setSelected(bool selected) { ButtonUI::setSelected(selected); setChosen(selected); }
};