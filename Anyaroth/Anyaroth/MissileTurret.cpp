#include "MissileTurret.h"
#include "Game.h"

MissileTurret::MissileTurret(Game* g, Boss1* boss, Vector2D pos, int activeFase) : Interactable(g, pos), _boss(boss), _activeFase(activeFase)
{
	Texture* missileTexture = g->getTexture("MissileTurret");
	addComponent<Texture>(missileTexture);

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->filterCollisions(OBJECTS, PLAYER);
	_body->setW(20);
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Deactivated, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::Activating, 12, false);
	_anim->addAnim(AnimatedSpriteComponent::Active, 4, true);
	_anim->addAnim(AnimatedSpriteComponent::Used, 11, false);

	_anim->playAnim(AnimatedSpriteComponent::Deactivated);

	Texture* _indicatorTexture = _interactIndicator->getComponent<Texture>();
	_interactIndicator->getComponent<TransformComponent>()->setPosition(pos.getX() + (missileTexture->getW() / missileTexture->getNumCols()) / 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2, pos.getY() - 30);
}

void MissileTurret::update(double deltaTime)
{
	Interactable::update(deltaTime);

	b2Vec2 bossPos = _boss->getComponent<BodyComponent>()->getBody()->GetPosition(), turretPos = _body->getBody()->GetPosition();
	Vector2D distancePos = Vector2D((bossPos.x - turretPos.x)*M_TO_PIXEL, (bossPos.y - turretPos.y)*M_TO_PIXEL);

	if (distancePos.getX() > 0)
		_anim->flip();
	else
		_anim->unFlip();

	if (usable && ready)
	{
		if (!_interactIndicator->isActive())
			_interactIndicator->setActive(true);
	}
	else
		_interactIndicator->setActive(false);

	if (usable)
	{
		ready = _boss->isbeetweenFases() && _boss->getLastFase() >= _activeFase;

		if (ready)
		{
			if (_anim->getCurrentAnim() != AnimatedSpriteComponent::Activating && _anim->getCurrentAnim() != AnimatedSpriteComponent::Active)
			{
				_anim->playAnim(AnimatedSpriteComponent::Activating);
				_game->getSoundManager()->playSFX("rocketLuncherUp");
			}
			else if (_anim->animationFinished() && _anim->getCurrentAnim() == AnimatedSpriteComponent::Activating)
				_anim->playAnim(AnimatedSpriteComponent::Active);
		}
	}
}

bool MissileTurret::interact()
{
	if (usable && ready)
	{
		_anim->playAnim(AnimatedSpriteComponent::Used);
		addChild(new Missile(_game, _transform->getPosition(), _boss));

		ready = false;
		usable = false;
	}
	return false;
}