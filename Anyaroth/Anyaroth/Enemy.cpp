#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "Bullet.h"
#include "Coin.h"
#include "AmmoPackage.h"
#include "AidKit.h"
#include "GameManager.h"

Enemy::Enemy(Game* g, Player* player, Vector2D pos, Texture* texture, string death, string hit, string meleeHit) : GameObject(g, "Enemy"), _player(player), _deathSound(death), _hitSound(hit), _meleeHit(meleeHit)
{
	_life = Life(50);

	_texture = texture;
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(pos.getX(), pos.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);
	
	_body->setW(20);
	_body->setH(30);

	_body->moveShape(b2Vec2(0, 0.6));
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<CustomAnimatedSpriteComponent>();
	_hurtParticle = _game->getTexture("Blood");
}

void Enemy::beginCollision(GameObject * other, b2Contact* contact)
{
	if (other->getTag() == "Bullet" || other->getTag() == "Melee")
	{
		int damage = other->getDamage();
		subLife(damage);

		BodyComponent* otherBody = other->getComponent<BodyComponent>();
		_contactPoint = otherBody->getBody()->GetPosition() + b2Vec2(otherBody->getW() / 2, otherBody->getH() / 2);

		if (other->getTag() == "Melee")
		{
			_dropMelee = true;
			_game->getSoundManager()->playSFX(_meleeHit);
		}
		else
		{
			_dropMelee = false;
			_game->getSoundManager()->playSFX(_hitSound);
		}
	}
	else if (other->getTag() == "Death")
		die();
}

void Enemy::update(double deltaTime)
{
	GameObject::update(deltaTime);

	if (!isDead() && inCamera())
		_body->getBody()->SetAwake(true);

	b2Vec2 playerPos = _player->getComponent<BodyComponent>()->getBody()->GetPosition(), enemyPos = _body->getBody()->GetPosition();
	_playerDistance = Vector2D((playerPos.x - enemyPos.x)*M_TO_PIXEL, (playerPos.y - enemyPos.y)*M_TO_PIXEL);

	if (isDead() && _drop)
	{
		_drop = false;
		drop();
	}
	if (_spawnParticles)
	{
		_spawnParticles = false;
		double center_x = _body->getBody()->GetPosition().x + _body->getW() / 2, center_y = _body->getBody()->GetPosition().y + _body->getH() / 2;
		Vector2D direction = Vector2D((_contactPoint.x - center_x), (center_y - _contactPoint.y));
		ParticleManager::GetParticleManager()->CreateSpray(_hurtParticle, Vector2D(_contactPoint.x*M_TO_PIXEL, _contactPoint.y*M_TO_PIXEL), direction, 4, 10, 30, 700, 5, 2);
	}
}

void Enemy::die()
{
	_anim->die();
	_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
	setDead(true);
	_body->filterCollisions(DEAD_ENEMIES, FLOOR | PLATFORMS);

	_game->getSoundManager()->playSFX(_deathSound);
}

void Enemy::drop()
{
	int rnd = _game->random(0, 100);

	if (rnd < 50 && _dropMelee)
	{
		addChild(new AidKit(_game, Vector2D(_body->getBody()->GetPosition().x*M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL), _player->getMaxLife() / 4));
	}
	else if (rnd < 15)
	{
		addChild(new AmmoPackage(_game, Vector2D(_body->getBody()->GetPosition().x*M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL), 1));
	}
	else if (rnd > 15 && GameManager::getInstance()->getCurrentLevel() != LevelManager::Boss3)
	{
		addChild(new Coin(_game, Vector2D(_body->getBody()->GetPosition().x*M_TO_PIXEL, _body->getBody()->GetPosition().y*M_TO_PIXEL), _coinValue));
	}
}

void Enemy::subLife(int damage)
{
	if (!isDead())
	{
		_life.subLife(damage);

		if (_life.getLife() == 0)
			die();
		else
		{
			_anim->hurt();
			_spawnParticles = true;
		}
	}
}

bool Enemy::inCamera()
{
	return _game->getCurrentState()->getMainCamera()->inCamera(Vector2D(_body->getBody()->GetPosition().x * M_TO_PIXEL, _body->getBody()->GetPosition().y * M_TO_PIXEL));
}