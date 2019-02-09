#include "BoxCollider.h"
#include "GameComponent.h"

BoxCollider::BoxCollider(GameComponent* obj) : PhysicsComponent(obj)
{
	_text = obj->getComponent<Texture>();
	_transform = obj->getComponent<TransformComponent>();

	_size = Vector2D(_text->getW()/ _text->getNumCols(), _text->getH()/ _text->getNumFils());

}

void BoxCollider::update()
{
	_collider.x = _transform->getPosition().getX();
	_collider.y = _transform->getPosition().getY();
	_collider.w = _size.getX() * _transform->getScale().getX();
	_collider.h = _size.getY() * _transform->getScale().getY();
}