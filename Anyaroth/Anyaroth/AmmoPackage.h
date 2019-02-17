#pragma once
#include "Collectable.h"

enum AmmoType
{
	Escopeta, Rifle, Pistola, Fusil	//Etc
};

class AmmoPackage : public Collectable
{
	private:
		AmmoType _type;
	public:
		AmmoPackage(Texture* texture, Vector2D iniPos, int value) : Collectable(texture, iniPos, value) {};
		~AmmoPackage() {};
};