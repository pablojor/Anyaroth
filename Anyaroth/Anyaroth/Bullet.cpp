#include "Bullet.h"
#include "Game.h"
#include <math.h>

Bullet::Bullet(Game* game) : GameObject(game)
{
	_texture = game->getTexture("PistolBullet");
	addComponent<Texture>(_texture);

	_transform = addComponent<TransformComponent>();
	_transform->setAnchor(0.5);

	_anim = addComponent<AnimatedSpriteComponent>();

	_body = addComponent<BodyComponent>();
	_body->filterCollisions(PLAYER_BULLETS, FLOOR | PLATFORMS | ENEMIES);
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);
	_body->getBody()->SetFixedRotation(true);
	_body->getBody()->SetGravityScale(0);
	_body->getBody()->SetActive(false);

	setActive(false);
}

void Bullet::beginCollision(GameObject * other, b2Contact* contact)
{
	if (getTag() == "Bullet" && (other->getTag() == "Ground" || other->getTag() == "Platform" || other->getTag() == "Enemy"))
		_collided = true;
	else if (getTag() == "EnemyBullet" && (other->getTag() == "Ground" || other->getTag() == "Platform" || other->getTag() == "Player"))
		_collided = true;

	contact->SetEnabled(false);
}

void Bullet::init(Texture* texture, const Vector2D& position, const double& speed, const double& damage, const double& angle, const double& range, const string& tag, string type)
{
	setTag(tag);
	_iniPos = position;
	_transform->setPosition(position);
	_speed = speed;
	_damage = damage;
	_range = range;

	_texture = texture;
	_transform->setRotation(angle);

	_body->getBody()->SetActive(true);
	_body->getBody()->SetTransform({ (float32)(position.getX() / M_TO_PIXEL), (float32)(position.getY() / M_TO_PIXEL) }, _body->getBody()->GetAngle());
	_body->getBody()->SetLinearVelocity(b2Vec2(0, 0));

	_anim->setTexture(texture);
	setAnimations(type);

	setActive(true);
}

void Bullet::update(const double& deltaTime)
{
	if (isActive())
	{
		double dist = _iniPos.distance(_transform->getPosition());

		if (dist < _range && !_collided)
		{
			GameObject::update(deltaTime);

			_body->getBody()->SetLinearVelocity(b2Vec2(_speed * cos(_transform->getRotation() * M_PI / 180.0), _speed * sin(_transform->getRotation() * M_PI / 180.0)));
			_aliveTime++;
		}
		else
			reset();
	}
}

void Bullet::reset()
{
	//_anim->

	_body->getBody()->SetActive(false);
	setActive(false);
	_aliveTime = 0;
	_collided = false;
}

void Bullet::changeFilter()
{
	_body->filterCollisions(ENEMY_BULLETS, FLOOR | PLATFORMS | PLAYER);
}

void Bullet::setAnimations(string type)
{

	if (type == "Bomb")
	{
		_anim->addAnim(AnimatedSpriteComponent::Default, 6, true);
		_anim->addAnim(AnimatedSpriteComponent::Destroy, 8, false);
	}
	else
	{
		_anim->addAnim(AnimatedSpriteComponent::Default, 4, true);
	}
}