#include "GroundEnemy.h"

GroundEnemy::GroundEnemy(Game* g, Player* player, Vector2D pos, Texture* texture) : Enemy(g, player, pos, texture) {}

void GroundEnemy::idle()
{
	if (!_stunned && _attacking == false)
	{
		_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::Idle);
	}
}

void GroundEnemy::moving(Vector2D& dir)
{
	if (!_stunned && _attacking == false)
	{
		_body->getBody()->SetLinearVelocity({ _speed*(float32)dir.getX(), _body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::EnemyWalk);
	}
}

void GroundEnemy::attack()
{
	if (!_stunned && _attacking == false)
	{
		_body->getBody()->SetLinearVelocity({ 0,_body->getBody()->GetLinearVelocity().y });
		_anim->playAnim(AnimatedSpriteComponent::EnemyAttack); //Llamas a animacion de ataque
		_time = 0;
		_attacking = true;
	}
}