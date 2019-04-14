#include "Camera.h"
#include "Game.h"
#include "TransformComponent.h"
#include "ParallaxBackGround.h"

void Camera::moveCamera(const double& deltaTime)
{
	SDL_Rect preChange = _cameraRect;
	if (_followedObject != nullptr)
	{
		auto a = _followedObject->getComponent<TransformComponent>();
		auto s = _followedObject->getComponent<CustomAnimatedSpriteComponent>();
		float playerOffsetX = (s->getTexture()->getW() / s->getTexture()->getNumCols()) / 2;

		//Aqui se lleva a cabo todo el movimiento
		float smoothSpeed = 7.0f;
		float offsetX = 100;
		Vector2D desiredPos;
		if (!s->isFlipped())
			desiredPos = Vector2D(a->getPosition().getX() + playerOffsetX - _cameraRect.w / 2 + offsetX, a->getPosition().getY() - _cameraRect.h / 2);
		else
			desiredPos = Vector2D(a->getPosition().getX() + playerOffsetX - _cameraRect.w / 2 - offsetX, a->getPosition().getY() - _cameraRect.h / 2);
			
		Vector2D smoothPos = Vector2D::Lerp(Vector2D(_cameraRect.x, _cameraRect.y), desiredPos, smoothSpeed * deltaTime / 1000.0f);

		if (abs(desiredPos.getX() - smoothPos.getX()) > 1.5f || abs(desiredPos.getY() - smoothPos.getY()) > 1.5f)
		{
			_cameraRect.x = smoothPos.getX();
			_cameraRect.y = smoothPos.getY();
		}
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

void Camera::smoothCameraZoom()
{
	if (_zoom != _zoomGoal)
	{
		bool _isMinor = false;
		if (_zoomGoal > _zoom) _isMinor = true;
		_isMinor ? _zoom++ : (_zoom - 1 < 0 ? _zoom = 0 : _zoom--);

		if ((_isMinor && _zoom >= _zoomGoal) || (!_isMinor && _zoom <= _zoomGoal))
			_zoom = _zoomGoal;

		setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom);
	}
}

Camera::Camera(GameObject * followObject)
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
	_zoomGoal = CAMERA_SCALE_FACTOR * zoomRatio;
	if (_zoomGoal < 0) _zoomGoal = 0;

	if (!smoothZoom)
	{
		_zoom = _zoomGoal;
		setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom);
	}
}

void Camera::update(const double& deltaTime)
{
	moveCamera(deltaTime);

	if (_backGround != nullptr)
		if (_backGround->checkCameraStatus(_cameraStatus))
			_backGround->update(deltaTime);

	smoothCameraZoom();
}

void Camera::render() const
{
	if (_backGround != nullptr) 
		_backGround->render();
}