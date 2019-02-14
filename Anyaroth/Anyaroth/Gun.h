#pragma once

#include "GameComponent.h"
#include "TransformComponent.h"
//#include "Game.h"

class Gun : public GameComponent
{
private:
	/*
	Clip es el tamaño del cargador,maxAmmo es la cantidad maxima de municion que puedes tener
	entre la que tienes actualmente en el cargador(ammoOnClip) y la que tienes fuera de él(leftAmmo)
	es decir leftAmmo + ammoOnClip !> maxAmmo.
	*/
	int _maxAmmo, _leftAmmo; //Munición máxima / munición actual
	int _maxClip, _leftClip; //Munición máxima en el cargador/ munición actual en el cargador
	GameComponent* _shootingObj = nullptr; //El objeto que usa el arma


	//Game* _game; //TEMPORAL
public:
	Gun(GameComponent* player ,int maxAmmunition, int magazine);
	virtual ~Gun();
	void update();
	void render() const {};
};

