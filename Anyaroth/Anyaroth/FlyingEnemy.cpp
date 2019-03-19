#include "FlyingEnemy.h"
#include "BodyComponent.h"
#include "Game.h"

FlyingEnemy::FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy( player,  g,  play,  texture, posIni, tag)
{
	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->filterCollisions(ENEMY_BULLETS, PLATFORMS, PLAYER);
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
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);

	double angle = atan2(_playerPos.getY() - _originalPos.getY(), _playerPos.getX() - _originalPos.getX()) * 180/M_PI;

	double xDir = (_playerPos.getX() < _bodyPos.getX()) ? -1 : 1;//(dis >  5 ) ? 1 : -1;
	if (abs(angle) > 90 && xDir == -1)
		xDir = 1;
	else if (abs(angle) > 90 && xDir == 1)
		xDir = -1;
	//Onda Sinusoidal vertical 
	double x = _prevPos.getX() + _velocity.getX() *xDir;
	double y = _originalPos.getY() +_amplitude * sin(_k * x - _angularFrequency * time / 1000 );

	_prevPos = Vector2D(x, y);
	Vector2D pos = _prevPos.rotateAroundPoint(angle, _originalPos);

	_body->getBody()->SetTransform(b2Vec2(pos.getX() / M_TO_PIXEL, pos.getY() / M_TO_PIXEL), 0);

}

void FlyingEnemy::beginCollision(GameComponent * other, b2Contact * contact)
{
	if (other->getTag() == "Suelo")
	{
		setActive(false);
		_play->KillObject(_itList);
	}
	else if (other->getTag() == "Player")
		_player->subLife(_damage);
}
