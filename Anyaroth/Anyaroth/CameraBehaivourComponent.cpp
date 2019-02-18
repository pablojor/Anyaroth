#include "CameraBehaivourComponent.h"
#include "TransformComponent.h"
#include "Camera.h"

CameraBehaivourComponent::CameraBehaivourComponent(GameComponent* obj) : PhysicsComponent(obj)
{
	auto camera = dynamic_cast<Camera*>(obj);
	_cameraRectRef = camera->getCameraRect();
}

void CameraBehaivourComponent::looseFollowedObject()
{
	if (_followedObject != nullptr)
		_followedObject = nullptr;
}

void CameraBehaivourComponent::update()
{
	if (_followedObject != nullptr)
	{
		auto a = _followedObject->getComponent<TransformComponent>()->getPosition();
		_cameraRectRef->x = a.getX();
		_cameraRectRef->y = a.getY();
	}

	//Aqui se haran los ajustes para que no se salga del mundo

}
