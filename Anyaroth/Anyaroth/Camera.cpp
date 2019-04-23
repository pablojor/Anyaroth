#include "Camera.h"
#include "Game.h"
#include "TransformComponent.h"
#include "ParallaxBackGround.h"

void Camera::moveCamera(const double& deltaTime)
{
	SDL_Rect preChange = _cameraRect;
	smoothMovement(deltaTime);

	//Aqui se haran los ajustes para que no se salga del mundo
	if (_cameraRect.x < 0)
		_cameraRect.x = 0;
	else if (_cameraRect.x > _xWorldBounds - _cameraRect.w)
		_cameraRect.x = _xWorldBounds - _cameraRect.w;

	if (_cameraRect.y < 0)
		_cameraRect.y = 0;
	else if (_cameraRect.y > _yWorldBounds - _cameraRect.h)
		_cameraRect.y = _yWorldBounds - _cameraRect.h;

	//Comparamos los cambios de la camara con su aspecto anterior
	if (preChange.x != _cameraRect.x)
	{
		_cameraStatus.first = true;
		_cameraRect.x - preChange.x > 0 ? _cameraStatus.second = 1 : _cameraStatus.second = -1;
	}
	else
		_cameraStatus.first = false;
}

void Camera::smoothMovement(const double & deltaTime)
{
	if (_followedObject != nullptr)
	{
		auto a = _followedObject->getComponent<TransformComponent>();
		auto s = _followedObject->getComponent<CustomAnimatedSpriteComponent>();
		float playerOffsetX = (s->getTexture()->getW() / s->getTexture()->getNumCols()) / 2;

		//Aqui se lleva a cabo todo el movimiento
		float smoothSpeed = 7.0f;	// Velocidad del smooth
		float offsetX = 40;			// Offset del objeto al centro de la pantalla

		Vector2D desiredPos;
		if (!s->isFlipped())
			desiredPos = Vector2D(a->getPosition().getX() + playerOffsetX - _cameraRect.w / 2 + offsetX, a->getPosition().getY() - _cameraRect.h / 2);
		else
			desiredPos = Vector2D(a->getPosition().getX() + playerOffsetX - _cameraRect.w / 2 - offsetX, a->getPosition().getY() - _cameraRect.h / 2);

		Vector2D smoothPos = Vector2D::Lerp(Vector2D(_cameraRect.x, _cameraRect.y), desiredPos, smoothSpeed * deltaTime / 1000.0f);

		//Eje X
		if (abs(desiredPos.getX() - smoothPos.getX()) > 12.f)		// 12.f porque cuanto mas grande, mas facil controlar los movimientos residuales
			_cameraRect.x = smoothPos.getX();
		//Eje Y
		if (abs(desiredPos.getY() - smoothPos.getY()) > 12.f)
			_cameraRect.y = smoothPos.getY();
	}
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

		if (CAMERA_ASPECT_RATIO_X * _zoom < _xWorldBounds && CAMERA_ASPECT_RATIO_Y * _zoom < _yWorldBounds)
			setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom);
	}
}

void Camera::shakeCamera(const double& deltaTime)
{
	if (_shakeIntensity > 0)
	{
		float randomX = -1.f + (double)rand() / (double)(RAND_MAX / 2);
		float randomY = -1.f + (double)rand() / (double)(RAND_MAX / 2);

		int x = _cameraRect.x + randomX * _shakeIntensity;
		int y = _cameraRect.y + randomY * _shakeIntensity;

		_cameraRect.x = x;
		_cameraRect.y = y;

		_shakeTime -= deltaTime;
		if (_shakeTime <= 0) {
			_shakeIntensity = -1;
		}
	}
}

void Camera::fadingControl(const double & deltaTime)
{
	if (_isFading)
	{
		if (_fadeMaxTime < 0)
			_fadeTime -= deltaTime;
		else
			_fadeTime += deltaTime;

		if (_fadeTime / _fadeMaxTime >= 1)
			_isFading = false;
	}
	else if (_fadeTime != 0)
		_fadeTime = 0;
}

Camera::Camera(Game* game, GameObject * followObject)
{
	fixCameraToObject(followObject);
	_game = game;
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

		if (CAMERA_ASPECT_RATIO_X * _zoom < _xWorldBounds && CAMERA_ASPECT_RATIO_Y * _zoom < _yWorldBounds)
			setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom);
	}
}

void Camera::setZoom(const int& zoom)
{
	_zoom = zoom;
	_zoomGoal = _zoom;

	if (CAMERA_ASPECT_RATIO_X * _zoom < _xWorldBounds && CAMERA_ASPECT_RATIO_Y * _zoom < _yWorldBounds)
		setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom);
}

void Camera::shake(const float& intensity, const float& time)
{
	_shakeIntensity = intensity;
	_shakeTime = time;
}

void Camera::fadeIn(const float & time)
{
	_fadeTime = 0;
	_fadeMaxTime = time;
	_isFading = true;
}

void Camera::fadeOut(const float & time)
{
	_fadeTime = 0;
	_fadeMaxTime = -time;
	_isFading = true;
}

void Camera::update(const double& deltaTime)
{
	moveCamera(deltaTime);
	shakeCamera(deltaTime);
	fadingControl(deltaTime);

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

void Camera::last_render() const 
{
	if (_isFading) {
		Texture tex = Texture(_game->getRenderer());
		Uint8 alpha = (_fadeTime / _fadeMaxTime) * 255;
		tex.load(_cameraRect.w, _cameraRect.h, 0, 0, 0, _fadeMaxTime < 0 ? alpha : 255 - alpha);
		tex.render({ 0, 0, GAME_RESOLUTION_X, GAME_RESOLUTION_Y });
	}
}

void Camera::setWorldBounds(const int & xBound, const int & yBound)
{
	_xWorldBounds = xBound;
	_yWorldBounds = yBound;
}
