#include "Camera.h"
#include "Game.h"
#include "TransformComponent.h"

Camera::Camera(GameComponent * followObject)
{
	fixCameraToObject(followObject);
}

void Camera::setCameraPosition(double x, double y)
{
	_cameraRect.x = x;
	_cameraRect.y = y;
}

void Camera::setCameraSize(double w, double h)
{
	_cameraRect.w = w;
	_cameraRect.h = h;
}

void Camera::looseFixedObject()
{
	if (_followedObject != nullptr)
		_followedObject = nullptr;

}

void Camera::update()
{
	if (_followedObject != nullptr)
	{
		auto a = _followedObject->getComponent<TransformComponent>()->getPosition();
		_cameraRect.x = a.getX() - _cameraRect.w / 2;
		_cameraRect.y = a.getY() - _cameraRect.h / 2;
	}

	//Aqui se haran los ajustes para que no se salga del mundo
	if (_cameraRect.x < 0)
	{
		_cameraRect.x = 0;
	}
	else if (_cameraRect.x > LEVEL_WIDTH - _cameraRect.w)
	{
		_cameraRect.x = LEVEL_WIDTH - _cameraRect.w;
	}


	if (_cameraRect.y < 0)
	{
		_cameraRect.y = 0;
	}
	else if (_cameraRect.y > LEVEL_HEIGHT - _cameraRect.h)
	{
		_cameraRect.y = LEVEL_HEIGHT - _cameraRect.h;
	}
}

void Camera::render()
{

}
