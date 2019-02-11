#include "BoxCollider.h"
#include "GameComponent.h"

BoxCollider::BoxCollider(GameComponent* obj) : PhysicsComponent(obj)
{
	auto _text = obj->getComponent<Texture>();
	_transform = obj->getComponent<TransformComponent>();

	_size = Vector2D(_text->getW()/ _text->getNumCols(), _text->getH()/ _text->getNumFils());

	_collider.w = _size.getX() * _transform->getScale().getX() * _scale.getX();
	_collider.h = _size.getY() * _transform->getScale().getY() * _scale.getY();
	_collider.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * _collider.w;
	_collider.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * _collider.h;

}

void BoxCollider::update()
{
	_collider.w = _size.getX() * _transform->getScale().getX() * _scale.getX();
	_collider.h = _size.getY() * _transform->getScale().getY() * _scale.getY();
	_collider.x = _transform->getPosition().getX() - _transform->getAnchor().getX() * _size.getX() * _transform->getScale().getX() + _offset.getX();
	_collider.y = _transform->getPosition().getY() - _transform->getAnchor().getY() * _size.getY() * _transform->getScale().getY() + _offset.getY();
}