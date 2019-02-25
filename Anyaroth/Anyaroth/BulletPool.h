#pragma once
#include "ObjectPool.h"
#include "AnimatedSpriteComponent.h"
#include "TransformComponent.h"
#include "MovingComponent.h"
#include "Bullet.h"
#include "Game.h"

class MovingComponent;

template<int SIZE>
class BulletPool :
	public ObjectPool<Bullet, SIZE>
{
private:
	Texture* _bulletTexture = nullptr;
	double _bulletSpeed = 0;
	int _bulletDamage = 0;
	int _bulletRange = 20;
	double _bulletAngle = 0;


	void initBullets();
public:
	BulletPool(Game* g, Texture* texture, double speed, int damage, double bulletAngle = 0, int bulletRange = 20) : _bulletTexture(texture), _bulletSpeed(speed), _bulletDamage(damage), _bulletAngle(bulletAngle), _bulletRange(bulletRange), ObjectPool<Bullet, SIZE>(g) { initBullets(); };
	virtual ~BulletPool() {};


	void addBullet(Vector2D pos, Vector2D dir, double angle);
};



template<int SIZE>
void BulletPool<SIZE>::initBullets() {
	for (int i = 0; i < SIZE; i++)
	{
		Bullet* b = ObjectPool<Bullet, SIZE>::getObject(i);
		b->init(_bulletTexture, _bulletSpeed, _bulletAngle, _bulletDamage);
	}
}


template<int SIZE>
void BulletPool<SIZE>::addBullet(Vector2D pos, Vector2D dir, double angle) {
	Bullet* b = ObjectPool<Bullet,SIZE>::getUnusedObject();

	if (b != nullptr) {

		b->reset();

		b->getComponent<TransformComponent>()->setPosition(pos.getX(), pos.getY());
		b->getComponent<TransformComponent>()->setRotation(angle);

		BodyComponent* _body = b->getComponent<BodyComponent>();

		_body->getBody()->SetActive(true);
		_body->getBody()->SetTransform({ (float32)(pos.getX()/ 8), (float32)(pos.getY() / 8) },_body->getBody()->GetAngle());
		_body->getBody()->SetLinearVelocity({ (float32)dir.getX() * 100,(float32)dir.getY() * 100 });

		
		//b->getComponent<MovingComponent>()->changeDir(dir.getX(),dir.getY()); //<- DESCOMENTAR PARA PROBAR CON FÍSICAS
		//b->setVelocity(dir*_bulletSpeed); //<- DESCOMENTAR PARA PROBAR SIN FÍSICAS
	}
}