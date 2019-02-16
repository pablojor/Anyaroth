#pragma once



////////////////////////////////////////////////////////////////
//		La clase Shooter implementa el método de disparo 
//		básico de las armas shoot().
//		Para hacer un nuevo tipo de disparo, hay que crear
//		una nueva clase que herede de Shooter y redefina
//		el método shoot().
////////////////////////////////////////////////////////////////

class Shooter
{
public:
	Shooter();
	virtual ~Shooter();

	virtual void shoot() {};
};

