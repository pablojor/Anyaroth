#pragma once
#include "GameComponent.h"

class Player : public GameComponent {
private:
	int _life;

public:
	Player(Texture* texture);
	~Player();

	void update();
};