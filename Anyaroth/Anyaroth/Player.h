#pragma once
#include "GameComponent.h"

class Player : public GameComponent {
private:
	int _life;

public:
	Player(Texture* texture, b2World* world);
	~Player();

	void update();
};