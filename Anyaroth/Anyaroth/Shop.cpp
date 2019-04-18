#include "Shop.h"
#include "Game.h"
#include "GameManager.h"

Shop::Shop(Game* g, Vector2D posIni, ShopMenu* shop) : _shop(shop), Interactable(g, posIni)
{
	addComponent<Texture>(g->getTexture("Coin"));
	auto _texture = getComponent<Texture>();

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Main, 6, true);

	_anim->playAnim(AnimatedSpriteComponent::Main);


	_body = addComponent<BodyComponent>();
	_body->getBody()->SetType(b2_kinematicBody);
	_body->setW(20);
	_body->setH(40);
	_body->getBody()->GetFixtureList()->SetSensor(true);
	_body->filterCollisions(OBJECTS, PLAYER); 

	auto _indicatorTexture = _interactIndicator->getComponent<Texture>();
	_interactIndicator->getComponent<TransformComponent>()->setPosition(posIni.getX() + (_texture->getW() / _texture->getNumCols()) / 2 - (_indicatorTexture->getW() / _indicatorTexture->getNumCols()) / 2 /*50*/, posIni.getY() - 30 /*180*/);

}

void Shop::interact()
{
	if (!_shop->isVisible())
		_shop->openShop(GameManager::getInstance()->getCurrentLevel());
}
