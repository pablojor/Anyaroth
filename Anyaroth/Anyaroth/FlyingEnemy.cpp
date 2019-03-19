#include "FlyingEnemy.h"
#include "BodyComponent.h"
#include "Game.h"

FlyingEnemy::FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy( player,  g,  play,  texture, posIni, tag)
{
	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->filterCollisions(ENEMIES, PLATFORMS, PLAYER);
	_body->getBody()->SetGravityScale(0);

	_originalPos= Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_playerBody = _player->getComponent<BodyComponent>();
	prevPos = _originalPos;
}


FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::update(double time)
{
	Enemy::update(time);

	_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);
	Vector2D _bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);

	double angle = atan2(_playerPos.getY() - _originalPos.getY(), _playerPos.getX() - _originalPos.getX()) * 180/M_PI;

	double dis = _playerPos.distance(_bodyPos);
	double xDir = (dis > 0) ? 1 : -1;
	//Ondas Sinusoidales vertical y horizontal
	double x = prevPos.getX() + _velocity.getX() *xDir;
	double y = _originalPos.getY() +_amplitude * sin(_k * x - _angularFrequency * time / 1000 );

	prevPos = Vector2D(x, y);
	Vector2D pos = prevPos.rotateAroundPoint(angle, _originalPos);

	_body->getBody()->SetTransform(b2Vec2(pos.getX() / M_TO_PIXEL, pos.getY() / M_TO_PIXEL), 0);

}

void FlyingEnemy::beginCollision(GameComponent * other, b2Contact * contact)
{
	if (other->getTag() == "Suelo")
	{
		setActive(false);
		_play->KillObject(_itList);
	}
}
