#pragma once
#include "GameComponent.h"

class Player : public GameComponent {
private:
	int _life;

public:
	Player(Texture* texture, Game* g);
	~Player();
	virtual void beginCollision(GameComponent* other);
	void update();
};