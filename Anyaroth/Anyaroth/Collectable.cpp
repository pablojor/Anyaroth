#include "Collectable.h"
#include "SpriteComponent.h"


Collectable::Collectable(Texture* texture, Vector2D iniPos, int value) : _value(value), GameComponent()
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(iniPos.getX(), iniPos.getY());

	addComponent<SpriteComponent>();

	//auto body = addComponente<BodyComponent>();
	//Modificacion del body (si es que necesita).
}
