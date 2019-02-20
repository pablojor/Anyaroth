#include "CameraBehaivourComponent.h"
#include "TransformComponent.h"
#include "Camera.h"
#include "Game.h"

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
		_cameraRectRef->x = a.getX() - _cameraRectRef->w / 2;
		_cameraRectRef->y = a.getY() - _cameraRectRef->h / 2;
	}

	//Aqui se haran los ajustes para que no se salga del mundo
	if (_cameraRectRef->x < 0)
	{
		_cameraRectRef->x = 0;
	}
	if (_cameraRectRef->y < 0)
	{
		_cameraRectRef->y = 0;
	}
	if (_cameraRectRef->x > LEVEL_WIDTH - _cameraRectRef->w)
	{
		_cameraRectRef->x = LEVEL_WIDTH - _cameraRectRef->w;
	}
	if (_cameraRectRef->y > LEVEL_HEIGHT - _cameraRectRef->h)
	{
		_cameraRectRef->y = LEVEL_HEIGHT - _cameraRectRef->h;
	}
}
