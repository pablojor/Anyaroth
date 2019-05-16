#include "Capsule.h"

Capsule::Capsule(Game* g, Player* player, Vector2D pos, Enemy* father) : GameObject(g), _player(player), _father(father)
{
	addComponent<Texture>(g->getTexture("Capsule"));

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(pos.getX(), pos.getY());

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::CapsuleDrop, 8, true);
	_anim->addAnim(AnimatedSpriteComponent::CapsuleSpawn, 17, false);
	_anim->playAnim(AnimatedSpriteComponent::CapsuleDrop);

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_dynamicBody);
	_body->getBody()->SetBullet(true);

	_body->setW(20);
	_body->setH(35);

	_body->moveShape(b2Vec2(0, 0.3));
	_body->getBody()->SetFixedRotation(true);
	_body->filterCollisions(DEAD_ENEMIES, FLOOR | PLATFORMS);
	_body->getBody()->SetGravityScale(3);

	//Sensor del suelo
	b2PolygonShape shape;
	shape.SetAsBox(8 / M_TO_PIXEL, 2 / M_TO_PIXEL, b2Vec2(0, 2.25), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = ENEMIES;
	fDef.filter.maskBits = FLOOR | PLATFORMS;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);
}

void Capsule::update(double deltaTime)
{
	GameObject::update(deltaTime);
	if (_anim->getCurrentAnim() == AnimatedSpriteComponent::CapsuleSpawn && _anim->animationFinished())
		spawn();
}

void Capsule::beginCollision(GameObject * other, b2Contact* contact)
{
	string otherTag = other->getTag();
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	//Deteccion del suelo
	if ((fA->IsSensor() || fB->IsSensor()) && (other->getTag() == "Ground" || other->getTag() == "Platform"))
	{
		_spawning = true;
		_anim->playAnim(AnimatedSpriteComponent::CapsuleSpawn);
		_game->getSoundManager()->playSFX("capsuleOpen");
	}
}