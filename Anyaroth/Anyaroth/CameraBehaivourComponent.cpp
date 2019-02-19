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
	SDL_Rect pos = *_cameraRectRef;
	if (_followedObject != nullptr)
	{
		auto a = _followedObject->getComponent<TransformComponent>()->getPosition();
		pos.x = a.getX() - _cameraRectRef->w / 2;
		pos.y = a.getY() - _cameraRectRef->h / 2;

		//Aqui se haran los ajustes para que no se salga del mundo
		if (pos.x < 0)
		{
			pos.x = 0;
		}
		if (pos.y < 0)
		{
			pos.y = 0;
		}
		if (pos.x > LEVEL_WIDTH - pos.w)
		{
			pos.x = LEVEL_WIDTH - pos.w;
		}
		if (pos.y > LEVEL_HEIGHT - pos.h)
		{
			pos.y = LEVEL_HEIGHT - pos.h;
		}
		_cameraRectRef->x = pos.x;
		_cameraRectRef->y = pos.y;
	}
}
