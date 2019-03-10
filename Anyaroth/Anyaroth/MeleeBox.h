#pragma once
#include "GameComponent.h"
#include "BodyComponent.h"

class MeleeBox : public GameComponent
{
private:
	Vector2D _pos, _size;
	int _type;
	double _damage, _angle = 90;
	BodyComponent* _body;
	Vector2D _center;
	double _r;
	int _dir;
public:
	MeleeBox(Game* g, double x, double y, double w, double h, double damage, Vector2D center, int dir,int type = 0);
	void update();
	void beginCollision(GameComponent * other, b2Contact* contact);
	virtual ~MeleeBox();
};

