#include "TutorialBuddy.h"

TutorialBuddy::TutorialBuddy(Game* g, Player* player, Vector2D pos) : GroundEnemy(g, player, pos, g->getTexture("EnemyMelee")), Enemy(g, player, pos, g->getTexture("TutorialBuddy"), "meleeDeath", "meleeHit", "meleeEnemyHit")
{
	_anim->addAnim(AnimatedSpriteComponent::EnemyIdle, 4, true, 200);
	_anim->addAnim(AnimatedSpriteComponent::EnemyWalk, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyAttack, 1, false);
	_anim->addAnim(AnimatedSpriteComponent::EnemyDie, 9, false);

	_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	_body->setW(20);
	_body->setH(30);

	_body->moveShape(b2Vec2(0, 0.1));
	_body->filterCollisions(ENEMIES, FLOOR | PLATFORMS | PLAYER_BULLETS | MELEE);
}

void TutorialBuddy::update(double deltaTime)
{
	GameObject::update(deltaTime);

	if (_anim->getCurrentAnim() == AnimatedSpriteComponent::EnemyDie && _anim->getCurrentFrame() >= 8)
		_anim->playAnim(AnimatedSpriteComponent::EnemyIdle);

	if (!isDead() && inCamera())
		_body->getBody()->SetAwake(true);
}

void TutorialBuddy::beginCollision(GameObject * other, b2Contact* contact)
{
	if (other->getTag() == "Bullet" || other->getTag() == "Melee")
	{
		_anim->playAnim(AnimatedSpriteComponent::EnemyDie);

		BodyComponent* otherBody = other->getComponent<BodyComponent>();
		_contactPoint = otherBody->getBody()->GetPosition() + b2Vec2(otherBody->getW() / 2, otherBody->getH() / 2);

		if (_game->random(0, 100) > 33)
			_game->getSoundManager()->playSFX("buddyHit1");
		else if (_game->random(0, 100) > 66)
			_game->getSoundManager()->playSFX("buddyHit2");
		else
			_game->getSoundManager()->playSFX("buddyHit3");
	}
}