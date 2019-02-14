#include "BoxCollider.h"
#include "GameComponent.h"

BoxCollider::BoxCollider(GameComponent* obj) : PhysicsComponent(obj)
{
	_text = obj->getComponent<Texture>();
	_transform = obj->getComponent<TransformComponent>();
	_body = obj->getComponent<BodyComponent>();

	_size = Vector2D(_text->getW()/ _text->getNumCols(), _text->getH()/ _text->getNumFils());

	_collider.x = _body->getBody()->GetPosition().x;
	_collider.y = _body->getBody()->GetPosition().y;
	_collider.w = _size.getX() * _transform->getScale().getX();
	_collider.h = _size.getY() * _transform->getScale().getY();

}

void BoxCollider::update()
{
	_collider.x = _body->getBody()->GetPosition().x;
	_collider.y = _body->getBody()->GetPosition().y;
	_collider.w = _size.getX() * _transform->getScale().getX();
	_collider.h = _size.getY() * _transform->getScale().getY();
}