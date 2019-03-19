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
		_cameraRect.x = 0;
	else if (_cameraRect.x > LEVEL_WIDTH - _cameraRect.w)
		_cameraRect.x = LEVEL_WIDTH - _cameraRect.w;

	if (_cameraRect.y < 0)
		_cameraRect.y = 0;
	else if (_cameraRect.y > LEVEL_HEIGHT - _cameraRect.h)
		_cameraRect.y = LEVEL_HEIGHT - _cameraRect.h;

	//Comparamos los cambios de la camara con su aspecto anterior
	if (preChange.x != _cameraRect.x)
	{
		_cameraStatus.first = true;
		_cameraRect.x - preChange.x > 0 ? _cameraStatus.second = 1 : _cameraStatus.second = -1;
	}
	else
		_cameraStatus.first = false;
}

void Camera::smoothCameraZoom(const double& time)
{
	float smoothVel = 0.5f;
	bool _isMinor = false;
	if (_zoom != _zoomGoal)
	{
		if (_zoomGoal > _zoom) _isMinor = true;
		_isMinor ? _zoom += smoothVel * time / 1000.0 : _zoom -= smoothVel * time / 1000.0;
		
		if ((_isMinor && _zoom >= _zoomGoal) || (!_isMinor && _zoom <= _zoomGoal))
			_zoom = _zoomGoal;

		setCameraSize(CAMERA_RESOLUTION_X * _zoom, CAMERA_RESOLUTION_Y * _zoom);
	}
}

Camera::Camera(GameComponent * followObject)
{
	fixCameraToObject(followObject);
}

Camera::~Camera()
{
	if (_backGround != nullptr) 
	{
		delete _backGround;
		_backGround = nullptr;
	}
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

void Camera::setZoom(const float& zoomRatio, const bool& smoothZoom)
{
	_zoomGoal = zoomRatio;
	if (!smoothZoom)
	{
		_zoom = _zoomGoal;
		setCameraSize(CAMERA_RESOLUTION_X * _zoom, CAMERA_RESOLUTION_Y * _zoom);
	}
}

void Camera::update(const double& time)
{
	moveCamera();
	if (_backGround != nullptr)
		if (_backGround->checkCameraStatus(_cameraStatus))
			_backGround->update(time);
	smoothCameraZoom(time);
}

void Camera::render() const
{
	if (_backGround != nullptr) 
		_backGround->render();
}