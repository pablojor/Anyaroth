#include "BotonLanzaMisiles.h"
#include "TransformComponent.h"
#include "BodyComponent.h"
#include "AnimatedSpriteComponent.h"
#include "Game.h"


BotonLanzaMisiles::BotonLanzaMisiles(Boss1* Boss, Game* g, PlayState* play, Texture* texture, Vector2D posIni, string tag) : _boss(Boss), _play(play), GameComponent(g, tag)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_transform->setPosition(posIni.getX(), posIni.getY());

	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_staticBody);
	_body->getBody()->SetBullet(true);

	_body->setW(20);
	_body->setH(20);
	_body->filterCollisions(MISILLAUNCHER, FLOOR );

	_body->getBody()->SetFixedRotation(true);

	_anim = addComponent<AnimatedSpriteComponent>();

	b2PolygonShape shape;
	shape.SetAsBox(5 / M_TO_PIXEL, 5 / M_TO_PIXEL, b2Vec2(0, 0 /*Dependera del sprite final */), 0);
	b2FixtureDef fDef;
	fDef.shape = &shape;
	fDef.filter.categoryBits = MISILLAUNCHER;
	fDef.filter.maskBits = PLAYER;
	fDef.isSensor = true;
	_body->addFixture(&fDef, this);
	
}


BotonLanzaMisiles::~BotonLanzaMisiles()
{
}

void BotonLanzaMisiles::beginCollision(GameComponent * other, b2Contact * contact)
{
	string otherTag = other->getTag();
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	if ((fA->IsSensor() || fB->IsSensor()) && otherTag == "Player" )
	{
		if(_boss->isbeetweenFases())
		_ableToFire = true;
	}
}

void BotonLanzaMisiles::endCollision(GameComponent * other, b2Contact * contact)
{
	string otherTag = other->getTag();
	auto fA = contact->GetFixtureA();
	auto fB = contact->GetFixtureB();

	if ((fA->IsSensor() || fB->IsSensor()) && otherTag == "Player")
	{
		_ableToFire = false;
	}
}

void BotonLanzaMisiles::update(double time)
{
	if (_ableToFire&&ready)
	{
		const Uint8* keyboard = SDL_GetKeyboardState(NULL);
		if (keyboard[SDL_SCANCODE_E])
		{
			ready = false;
			shoot();
		}
	}
}

void BotonLanzaMisiles::shoot()
{
	MisilBoss1 * misil = new MisilBoss1(_boss, _game, _play, _game->getTexture("PistolBullet"), _transform->getPosition(), "Misil");
	_play->addObject(misil);
}
