#pragma once
#include "GameComponent.h"
class Player :
	public GameComponent
{
private:
	int life;
public:
	Player(Texture* texture);
	virtual ~Player();

	void update();
};

