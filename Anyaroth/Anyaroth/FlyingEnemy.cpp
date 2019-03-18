#include "FlyingEnemy.h"
#include "BodyComponent.h"
#include "Game.h"

FlyingEnemy::FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy( player,  g,  play,  texture, posIni, tag)
{
	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->filterCollisions(ENEMIES, NULL);
	_body->getBody()->SetGravityScale(0);

	_originalPos= Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_playerTransform = _player->getComponent<TransformComponent>();
}


FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::update(double time)
{
	Enemy::update(time);
	_velocity += 0.5;
	_playerPos=_playerTransform->getPosition();
	double angle = atan2(_transform->getPosition().getY() - _playerPos.getY(), _transform->getPosition().getX() - _playerPos.getX());

	double x = _originalPos.getX() + _velocity;
	double y = _originalPos.getY() + _amplitude * sin(_k * x - _angularFrequency * time / 1000);

	_body->getBody()->SetTransform(b2Vec2(x/M_TO_PIXEL, y/M_TO_PIXEL), 0);
}
