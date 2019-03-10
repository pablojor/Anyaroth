#pragma once
#include "ObjectPool.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "Bullet.h"
#include "Game.h"

class MovingComponent;

template<int SIZE>
class BulletPool : public ObjectPool<Bullet, SIZE>
{
private:
	Texture* _bulletTexture = nullptr;
	double _bulletSpeed = 0;
	int _bulletDamage = 0;
	int _bulletRange = 0;
	double _bulletAngle = 0;
	int _bulletNumFrames = 0;
	GameState* _current;
	void initBullets();

public:
	BulletPool(Game* g, Texture* texture, GameState* state, double speed, int damage, int bulletRange = 20, double bulletAngle = 0, int bulletNumFrames = 4) :
		_bulletTexture(texture), _bulletSpeed(speed), _bulletDamage(damage), _bulletRange(bulletRange), _bulletAngle(bulletAngle), _bulletNumFrames(bulletNumFrames), _current(state), ObjectPool<Bullet, SIZE>(g) { initBullets(); };
	virtual ~BulletPool() {};

	void addBullet(Vector2D pos, Vector2D dir, double angle);
	void changePoolTag(string tag);
	void changePoolFilter(uint16 ownCategory, uint16 collidesWith, int groupIndex);
};



template<int SIZE>
void BulletPool<SIZE>::initBullets() {
	for (int i = 0; i < SIZE; i++)
	{
		Bullet* b = ObjectPool<Bullet, SIZE>::getObject(i);
		b->init(_bulletTexture, _current, _bulletSpeed, _bulletDamage, _bulletAngle, _bulletRange, _bulletNumFrames);
	}
}


template<int SIZE>
void BulletPool<SIZE>::addBullet(Vector2D pos, Vector2D dir, double angle) {
	Bullet* b = ObjectPool<Bullet, SIZE>::getUnusedObject();

	if (b != nullptr) {

		b->reset(pos);

		b->getComponent<TransformComponent>()->setPosition(pos.getX(), pos.getY());
		b->getComponent<TransformComponent>()->setRotation(angle);

		BodyComponent* _body = b->getComponent<BodyComponent>();

		_body->getBody()->SetActive(true);
		_body->getBody()->SetTransform({ (float32)(pos.getX() / 8/*M_TO_PIXEL*/), (float32)(pos.getY() / 8/*M_TO_PIXEL*/) }, _body->getBody()->GetAngle());
		_body->getBody()->SetLinearVelocity({ (float32)(dir.getX() * _bulletSpeed),(float32)(dir.getY() * _bulletSpeed) });

		AnimatedSpriteComponent* _anim = b->getComponent<AnimatedSpriteComponent>();
		_anim->playAnim(AnimatedSpriteComponent::Default);

		//b->getComponent<MovingComponent>()->changeDir(dir.getX(),dir.getY()); //<- DESCOMENTAR PARA PROBAR CON F�SICAS
		//b->setVelocity(dir*_bulletSpeed); //<- DESCOMENTAR PARA PROBAR SIN F�SICAS
	}
}

template<int SIZE>
void BulletPool<SIZE>::changePoolTag(string tag) {
	for (int i = 0; i < SIZE; i++)
	{
		Bullet* b = ObjectPool<Bullet, SIZE>::getObject(i);
		b->setTag(tag);
	}
}

template<int SIZE>
inline void BulletPool<SIZE>::changePoolFilter(uint16 ownCategory, uint16 collidesWith, int groupIndex)
{
	for (int i = 0; i < SIZE; i++)
	{
		Bullet* b = ObjectPool<Bullet, SIZE>::getObject(i);
		b->getComponent<BodyComponent>()->filterCollisions(ownCategory, collidesWith, groupIndex);
	}
}
