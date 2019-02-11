#include "BoxCollider.h"
#include "GameComponent.h"

BoxCollider::BoxCollider(GameComponent* obj) : PhysicsComponent(obj)
{
	auto _text = obj->getComponent<Texture>();
	_transform = obj->getComponent<TransformComponent>();

	_size = Vector2D(_text->getW()/ _text->getNumCols(), _text->getH()/ _text->getNumFils());

	_collider.w = _size.getX() * _transform->getScale().getX();
	_collider.h = _size.getY() * _transform->getScale().getY();
	_collider.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * _collider.w;
	_collider.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * _collider.h;

}

void BoxCollider::setOffset()
{

}

void BoxCollider::update()
{
	_collider.w = _size.getX() * _transform->getScale().getX();
	_collider.h = _size.getY() * _transform->getScale().getY();
	_collider.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * _collider.w;
	_collider.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * _collider.h;
}