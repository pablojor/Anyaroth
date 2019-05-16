#include "LaserContainer.h"

LaserContainer::LaserContainer(Game* g, Vector2D pos, Texture* container, Texture* laser, Player* player) : GameObject(g)
{
	addComponent<Texture>(container);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(pos.getX(), pos.getY());
	transform->setScale(0.75);

	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::LaserClosed, 1, true);
	_anim->addAnim(AnimatedSpriteComponent::LaserClosing, 4, false, 150);
	_anim->addAnim(AnimatedSpriteComponent::LaserOpened, 1, true);
	_anim->addAnim(AnimatedSpriteComponent::LaserOpening, 4, false, 150);
	_anim->playAnim(AnimatedSpriteComponent::LaserClosed);

	_laser = new Laser(g, pos, laser, player, 4);

	addChild(_laser);
}
void LaserContainer::render(Camera* c) const
{
	//Llama al render de los hijos
	if (_laser->isActive())
		_laser->render(c);

	for (auto rc : getRenderComponents())
		rc->render(c);
}