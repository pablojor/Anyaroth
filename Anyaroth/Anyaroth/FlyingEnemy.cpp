#include "FlyingEnemy.h"
#include "BodyComponent.h"
#include "Game.h"

FlyingEnemy::FlyingEnemy(Player* player, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : Enemy( player,  g,  play,  texture, posIni, tag)
{
	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 13, true);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 18, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->filterCollisions(ENEMY_BULLETS, PLATFORMS | PLAYER);
	_body->getBody()->SetGravityScale(0);
	_body->getBody()->GetFixtureList()->SetSensor(true);

	_prevPos= Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);
	_playerBody = _player->getComponent<BodyComponent>();
}

FlyingEnemy::~FlyingEnemy() {}

void FlyingEnemy::update(double time)
{
	Enemy::update(time);

	_playerPos = Vector2D(_playerBody->getBody()->GetPosition().x * M_TO_PIXEL, _playerBody->getBody()->GetPosition().y * M_TO_PIXEL);
	_bodyPos = Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL);

	Vector2D dir = Vector2D((_playerPos.getX() < _bodyPos.getX()) ? -1 : 1, (_playerPos.getY() < _bodyPos.getY()) ? -1 : 1);

	//Onda Sinusoidal vertical 
	double x = _bodyPos.getX() + _velocity.getX() *dir.getX();

	double prevY = _prevPos.getY() + _velocity.getY() *dir.getY();
	_prevPos = Vector2D(x, prevY);

	double y = prevY + _amplitude * sin(_k * x - _angularFrequency * time / 1000);

	_body->getBody()->SetTransform(b2Vec2(x / M_TO_PIXEL, y / M_TO_PIXEL), 0);
}

void FlyingEnemy::beginCollision(GameComponent * other, b2Contact * contact)
{
	if (other->getTag() == "Player")
		_player->subLife(_damage);

	setActive(false);

	destroy();
}