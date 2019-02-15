#pragma once
#include "GameComponent.h"
#include "BodyComponent.h"

class Gun : public GameComponent
{
private:
	/*
	Clip es el tamaño del cargador,maxAmmo es la cantidad maxima de municion que puedes tener
	entre la que tienes actualmente en el cargador(ammoOnClip) y la que tienes fuera de él(leftAmmo)
	es decir leftAmmo + ammoOnClip !> maxAmmo.
	*/
	int _maxAmmo, _leftAmmo;
	int _clip, _ammoOnClip;
	BodyComponent* _playerTransform;

public:
	Gun(Texture* texture, GameComponent* player ,int maxAmmunition, int magazine, Game* g);
	virtual ~Gun();
	void update();
};