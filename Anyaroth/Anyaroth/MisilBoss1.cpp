#include "MisilBoss1.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"

MisilBoss1::MisilBoss1(Boss1* Boss, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : _boss(Boss), _play(play), GameComponent(g, tag)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(posIni.getX(), posIni.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_staticBody);
	_body->getBody()->SetBullet(true);

	_body->setW(20);
	_body->setH(20);
	_body->filterCollisions(MISIL, ENEMIES);

	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();

}


MisilBoss1::~MisilBoss1()
{
}

void MisilBoss1::beginCollision(GameComponent * other, b2Contact * contact)
{
	contact->SetEnabled(false);
	setActive(false);
	_body->filterCollisions(MISIL, DEAD_ENEMIES);
}

void MisilBoss1::update(double time)
{
	if (isActive())
	{
		BodyComponent* help = _boss->getComponent<BodyComponent>();
		float x = help->getBody()->GetPosition().x, myX = _body->getBody()->GetPosition().x;
		float y = help->getBody()->GetPosition().y, myY = _body->getBody()->GetPosition().y;

		if (myX<x && myX - x>0.01)
		{
			myX -= 0.01 / 8;
		}
		else if (myX > x && myX - x < -0.01)
			myX += 0.01 / 8;
		else
			myX -= (myX - x) / 8;

		if (myY<y && myY - y>0.01)
		{
			myY -= 0.01 / 8;
		}
		else if (myY > y && myY - y < -0.01)
			myY += 0.01 / 8;
		else
			myY -= (myY - y) / 8;
		_body->getBody()->SetTransform(b2Vec2(myX, myY), 0);
		_transform->setPosition(Vector2D(myX * 8, myY * 8));
	}
	
}
