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

	public:
		AmmoPackage(AmmoType type, Game* g, Texture* texture, Vector2D iniPos, int value) : _type(type), Collectable(g, texture, iniPos, value) {};
		virtual ~AmmoPackage() {};

		string getType();
};