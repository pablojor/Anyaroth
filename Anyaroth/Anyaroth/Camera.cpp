#include "Camera.h"
#include "Game.h"
#include "TransformComponent.h"
#include "ParallaxBackGround.h"

void Camera::moveCamera()
{
	SDL_Rect preChange = _cameraRect;
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

	//Comparamos los cambios de la camara con su aspecto anterior
	if (preChange.x != _cameraRect.x)
	{
		_cameraIsMoving.first = true;
		_cameraRect.x - preChange.x > 0 ? _cameraIsMoving.second = 1 : _cameraIsMoving.second = -1;
	}
	else
		_cameraIsMoving.first = false;
}

bool Camera::checkParallax()
{
	if (_cameraIsMoving.first)
	{
		auto a = dynamic_cast<ParallaxBackGround*>(_backGround);
		if (a != nullptr)
			_cameraIsMoving.second == 1 ? a->changeDirection(true) : a->changeDirection(false);
		return true;
	}
	return false;
}

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
	moveCamera();
	if (checkParallax())
		_backGround->update();
}

void Camera::render() const
{
	_backGround->render();
}
