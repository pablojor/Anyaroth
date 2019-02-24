#pragma once
#include "GameComponent.h"

class Player;

class Enemy : public GameComponent
{
private:
	int _life;
public:
	Enemy(Texture* texture,Vector2D posIni, Player* player, Game* g, string tag);
	virtual ~Enemy();

	virtual void setLife(double amount);
	virtual void addLife(double amount);
	virtual void subLife(double amount);
	virtual void die();

	virtual void beginCollision(GameComponent* other);

	void update();
};