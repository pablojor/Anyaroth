#include "Missile.h"
#include "Game.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "ParticleManager.h"

Missile::Missile(Game* g, Vector2D pos, GameObject* target) : GameObject(g, "Misil"), _target(target)
{
	addComponent<Texture>(g->getTexture("Missile"));

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(pos.getX(), pos.getY());


	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->getBody()->SetBullet(true);

	_body->setW(20);
	_body->setH(20);
	_body->filterCollisions(MISIL, ENEMIES);

	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Default, 4, true);
	_anim->addAnim(AnimatedSpriteComponent::Destroy, 6, false);

	_anim->playAnim(AnimatedSpriteComponent::Default);

	_targetBody = _target->getComponent<BodyComponent>();

	_targetPos = Vector2D(_targetBody->getBody()->GetPosition().x * M_TO_PIXEL, _targetBody->getBody()->GetPosition().y * M_TO_PIXEL);
	_myPos = Vector2D(_body->getBody()->GetPosition().x  * M_TO_PIXEL, _body->getBody()->GetPosition().y  * M_TO_PIXEL);

	_angle = atan2(_targetPos.getY() - _myPos.getY(), _targetPos.getX() - _myPos.getX()) * 180 / M_PI;

	g->getSoundManager()->playSFX("rocketLaunch");
}

void Missile::beginCollision(GameObject * other, b2Contact * contact)
{
	_body->getBody()->SetLinearVelocity(b2Vec2(0, 0));
	_anim->playAnim(AnimatedSpriteComponent::Destroy);

	contact->SetEnabled(false);
	setActive(false);

	_body->filterCollisions(MISIL, 0);

	_game->getSoundManager()->playSFX("martyrExplosion");
}

void Missile::update(double deltaTime)
{
	GameObject::update(deltaTime);

	if (isActive())
	{
		_targetPos = Vector2D(_targetBody->getBody()->GetPosition().x * M_TO_PIXEL, _targetBody->getBody()->GetPosition().y * M_TO_PIXEL);
		_myPos = Vector2D(_body->getBody()->GetPosition().x  * M_TO_PIXEL, _body->getBody()->GetPosition().y  * M_TO_PIXEL);

		ParticleManager::GetParticleManager()->CreateFountain(_game->getTexture("Smoke"), Vector2D(_transform->getPosition().getX() + _body->getW()*M_TO_PIXEL *-sin(_transform->getRotation()), _transform->getPosition().getY() + _body->getH()* M_TO_PIXEL *cos(_transform->getRotation())), Vector2D(0, 0), 0, 1, 15, 600, 10, 100, 0.5);

		_angle = atan2(_targetPos.getY() - _myPos.getY(), _targetPos.getX() - _myPos.getX()) * 180 / M_PI;

		if (_targetPos.distance(_myPos) < _velocity.distance(Vector2D()) * 2)
			_velocity = { _velocity.getX() / 2, _velocity.getY() / 2 };

		_body->getBody()->SetLinearVelocity(b2Vec2(_velocity.getX() * cos(_angle), _velocity.getY() * sin(_angle)));
		_transform->setRotation(_angle);

		if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::Destroy)
		{
			_anim->playAnim(AnimatedSpriteComponent::Default);
			destroy();
		}
	}
}