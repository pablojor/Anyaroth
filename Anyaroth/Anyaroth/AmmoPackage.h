#pragma once
#include "Collectable.h"

enum AmmoType
{
	PistolaBasica, PistolaRafagas, PistolaPlasma, EscopetaBasica, Rifle, Fusil
};

class AmmoPackage : public Collectable
{
	private:
		AmmoType _type;
		string _tag = "AmmoPackage";

	public:
		AmmoPackage(AmmoType type, Game* g, Texture* texture, Vector2D iniPos, int value) : _type(type), Collectable(g, texture, iniPos, value, _tag) {};
		virtual ~AmmoPackage() {};

		string getType();
};