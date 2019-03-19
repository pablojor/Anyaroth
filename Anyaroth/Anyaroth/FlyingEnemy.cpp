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
	_playerTransform = _player->getComponent<TransformComponent>();
}


FlyingEnemy::~FlyingEnemy()
{
}

void FlyingEnemy::update(double time)
{
	Enemy::update(time);
	acumulatedVel += _velocity.getX();
	_playerPos=_playerTransform->getPosition();
	double angle = atan2(_playerPos.getY() - _transform->getPosition().getY(), _playerPos.getX() - _transform->getPosition().getX());
	Vector2D dir = Vector2D(cos(angle), sin(angle));
	Vector2D intDir = Vector2D((dir.getX() > 0) ? 1 : -1 , (dir.getY() > 0) ? 1 : -1);

	//Ondas Sinusoidales vertical y horizontal
	double x = _body->getBody()->GetPosition().x * M_TO_PIXEL + _velocity.getX() * intDir.getX();
	double y = _originalPos.getY() +_amplitude * sin(_k * x - _angularFrequency * time / 1000);

	double y1 = _body->getBody()->GetPosition().y * M_TO_PIXEL + _velocity.getY() * intDir.getY();
	double x1 = _originalPos.getX() + _amplitude * cos(_k * y1 + _angularFrequency * time / 1000);

	double x2 = _body->getBody()->GetPosition().x * M_TO_PIXEL + _velocity.getX() * intDir.getX();
	double y2 = (_body->getBody()->GetPosition().y * M_TO_PIXEL + _velocity.getY() * intDir.getY()) + (_amplitude * sin(_angularFrequency * time / 1000));

	double y3 = _body->getBody()->GetPosition().y * M_TO_PIXEL + _velocity.getY() * intDir.getY();
	double x3 = _originalPos.getX()+ (acumulatedVel* intDir.getX()) + _amplitude * cos(_k * y1 + _angularFrequency * time / 1000);

	_body->getBody()->SetTransform(b2Vec2(x2 / M_TO_PIXEL, y2 / M_TO_PIXEL), 0);

	//Seguimiento del jugador
	//_body->getBody()->SetLinearVelocity(b2Vec2(_velocity * cos(angle), _velocity * sin(angle)));




}

void FlyingEnemy::beginCollision(GameComponent * other, b2Contact * contact)
{

}
