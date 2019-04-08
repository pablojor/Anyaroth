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

Bullet::~Bullet()
{
}

void Bullet::beginCollision(GameObject * other, b2Contact* contact)
{
	if (isActive() && _effect != nullptr)
		_effect->beginCollision(this, other, contact);
}

void Bullet::endCollision(GameObject * other, b2Contact* contact)
{
	if (isActive() && _effect != nullptr)
		_effect->endCollision(this, other, contact);
}

void Bullet::init(Texture* texture, const Vector2D& position, const double& speed, const double& damage, const double& angle, const double& range, const string& tag, EffectInterface* effect, BulletAnimType type)
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




	_effect = effect;
	_effect->init(this);

	_anim->setTexture(texture);
	setAnimations(type);

	setActive(true);
}

void Bullet::update(const double& deltaTime)
{
	/*if (isActive())
	{
		double dist = _iniPos.distance(_transform->getPosition());
		GameObject::update(deltaTime);

		if (dist < _range && !_collided)
		{
			_body->getBody()->SetLinearVelocity(b2Vec2(_speed * cos(_transform->getRotation() * M_PI / 180.0), _speed * sin(_transform->getRotation() * M_PI / 180.0)));
			_aliveTime++;
		}
		else
		{

			if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::Destroy)
			{
				reset();
			}
			else
			{
				_body->getBody()->SetActive(false);
				_anim->playAnim(AnimatedSpriteComponent::Destroy);
			}
		}
	}*/
	if (isActive() && _effect != nullptr)
		_effect->update(this, deltaTime);
}

/* reset()
_anim->playAnim(AnimatedSpriteComponent::Default);
setActive(false);
_aliveTime = 0;
_collided = false;*/

void Bullet::changeFilter()
{
	_body->filterCollisions(ENEMY_BULLETS, FLOOR | PLATFORMS | PLAYER);
}

void Bullet::setAnimations(BulletAnimType type)
{
	switch (type)
	{
	case SpentaBomb:
		_anim->addAnim(AnimatedSpriteComponent::Default, 6, true);
		_anim->addAnim(AnimatedSpriteComponent::Destroy, 8, false);
		break;
	case SpentaOrb:
		_anim->addAnim(AnimatedSpriteComponent::Default, 3, true);
		_anim->addAnim(AnimatedSpriteComponent::Destroy, 10, false);
		break;
	case ShotGunBullet:
		_anim->addAnim(AnimatedSpriteComponent::Default, 2, true);
		break;
	case BHBullet:
		_anim->addAnim(AnimatedSpriteComponent::Default, 2, true);
		_anim->addAnim(AnimatedSpriteComponent::Destroy, 5, false);
		break;
	case Default:
	default:
		_anim->addAnim(AnimatedSpriteComponent::Default, 4, true);
		_anim->addAnim(AnimatedSpriteComponent::Destroy, 4, false);
		break;
	}
}
void Bullet::reset()
{
	if (isActive() && _effect != nullptr)
	{
		_effect->reset(this);
		_anim->reset();
	}

}