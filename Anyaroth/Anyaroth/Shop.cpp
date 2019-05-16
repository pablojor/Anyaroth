#include "Game.h"
#include "GameManager.h"
#include "Shop.h"

Shop::Shop(Game* g, Vector2D posIni, ShopMenu* shop) : _shop(shop), Interactable(g, Vector2D(posIni.getX() - 136, posIni.getY() - 249))
{
	//----EDIFICIO----//

	addComponent<Texture>(g->getTexture("Shop"));

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Default, 8, true, 160);

	_anim->playAnim(AnimatedSpriteComponent::Default);

	//----PUERTA----//

	_shopDoor = new SpriteObject(g, g->getTexture("ShopDoor"), posIni);

	_shopDoorAnim = _shopDoor->getComponent<AnimatedSpriteComponent>();
	_shopDoorAnim->reset();
	_shopDoorAnim->addAnim(AnimatedSpriteComponent::Closed, 1, true);
	_shopDoorAnim->addAnim(AnimatedSpriteComponent::Opened, 5, false);

	_shopDoorAnim->playAnim(AnimatedSpriteComponent::Closed);

	int doorH = 43, doorW = 38;

	_body = addComponent<BodyComponent>();
	_body->setH(doorH);
	_body->setW(doorW);
	_body->moveShape(b2Vec2(-1.25, _body->getH() + 12.35));
	_body->getBody()->SetType(b2_kinematicBody);
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->filterCollisions(OBJECTS, PLAYER);

	auto _indicatorTexture = _interactIndicator->getComponent<Texture>();
	_interactIndicator->getComponent<TransformComponent>()->setPosition(posIni.getX() + doorW / 2 + 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2 /*50*/,
																		posIni.getY() - 30 /*180*/);

	addChild(_shopDoor);
}

void Shop::update(double deltaTime)
{
	Interactable::update(deltaTime);

	if (goIn && _shopDoorAnim->getCurrentAnim() == AnimatedSpriteComponent::Opened && _shopDoorAnim->animationFinished())
	{
		_shop->openShop();
		_shopDoorAnim->playAnim(AnimatedSpriteComponent::Closed);
		goIn = false;
	}
}

bool Shop::interact()
{
	if (!_shop->isVisible())
	{
		_game->getCurrentState()->getMainCamera()->fadeOut(500);
		goIn = true;
		_shopDoorAnim->playAnim(AnimatedSpriteComponent::Opened);
	}
	return false;
}
