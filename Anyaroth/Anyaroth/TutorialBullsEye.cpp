#include "TutorialBullsEye.h"

TutorialBullsEye::TutorialBullsEye(Game* g, Player* player, Vector2D pos) : Enemy( g,  player,  pos, g->getTexture("TutorialBullseye"))
{
	_body->setW(20);
	_body->setH(20);

	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
	_body->getBody()->SetGravityScale(0);

	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 4, true, 160);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 8, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 4, true, 160);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);
}

void TutorialBullsEye::update(double deltaTime)
{
	GameObject::update(deltaTime);

	if (!isDead() && inCamera())
		_body->getBody()->SetAwake(true);
}

void TutorialBullsEye::beginCollision(GameObject * other, b2Contact* contact)
{
	if (!_hasBeenHit && other->getTag() == "Bullet")
	{
		_hasBeenHit = true;
		_anim->playAnim(AnimatedSpriteComponent::EnemyDie);
		_game->getSoundManager()->playSFX("bullseyeHit");
	}
}