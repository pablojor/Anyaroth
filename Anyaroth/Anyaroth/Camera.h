#pragma once
#include "GameObject.h"
#include "BackGround.h"
#include <utility>
#include "Vector2D.h"

//Valores predeterminados
const int CAMERA_ASPECT_RATIO_X = 16;
const int CAMERA_ASPECT_RATIO_Y = 9;
const int CAMERA_SCALE_FACTOR = 30;
const int CAMERA_RESOLUTION_X = CAMERA_ASPECT_RATIO_X * CAMERA_SCALE_FACTOR;
const int CAMERA_RESOLUTION_Y = CAMERA_ASPECT_RATIO_Y * CAMERA_SCALE_FACTOR;


class Camera
{
private:
	Game* _game = nullptr;
	SDL_Rect _cameraRect;
	BackGround* _backGround = nullptr;

	GameObject* _followedObject = nullptr;

	int _xWorldBounds = 0, _yWorldBounds = 0;

	void moveCamera(const double& deltaTime);
	void smoothMovement(const double& deltaTime);
	void smoothCameraZoom(/*const double& deltaTime*/);
	void shakeCamera(const double& deltaTime);
	void fadingControl(const double& deltaTime);

	pair<bool, int> _cameraStatus = pair<bool, int>(false, 0);
	int _zoom = CAMERA_SCALE_FACTOR; int _zoomGoal = CAMERA_SCALE_FACTOR;

	float _shakeIntensity = -1.f;
	float _shakeTime = 0.f;

	float _fadeTime = 0.f;
	float _fadeMaxTime = 0.f;
	bool _isFading = false;

public:
	Camera(Game* game) : _game(game) {};
	Camera(Game* game, GameObject* followObject);
	Camera(Game* game, SDL_Rect rect) : _cameraRect(rect), _game(game) {}
	~Camera();

	inline SDL_Rect* getCameraRect() { return &_cameraRect; }

	void setCameraPosition(double x, double y);
	void setCameraSize(double w, double h);

	inline void setBackGround(BackGround* bg) { _backGround = bg; }

	inline Vector2D getCameraPosition() const { return Vector2D(_cameraRect.x, _cameraRect.y); }
	inline Vector2D getCameraSize() const { return Vector2D(_cameraRect.w, _cameraRect.h); }

	inline bool inCamera(const Vector2D& pos) const { return (pos.getX() > _cameraRect.x && pos.getX() < _cameraRect.x + _cameraRect.w && pos.getY() > _cameraRect.y && pos.getY() < _cameraRect.y + _cameraRect.h); }
	inline bool inCameraX(const Vector2D& pos) const { return (pos.getX() > _cameraRect.x && pos.getX() < _cameraRect.x + _cameraRect.w); }

	void fixCameraToObject(GameObject* object) { _followedObject = object; };
	void looseFixedObject();

	inline GameObject* getFollowedObject() const { return _followedObject; };

	void setZoom(const float& zoomRatio, const bool& smoothZoom = false);
	void setZoom(const int& zoom);
	inline int getZoom() const { return _zoom; }
	inline float getZoomRatio() const { return float(_zoom) / float(CAMERA_SCALE_FACTOR); };

	inline void zoomOut() { _zoom++; _zoomGoal = _zoom; if (CAMERA_ASPECT_RATIO_X * _zoom < _xWorldBounds && CAMERA_ASPECT_RATIO_Y * _zoom < _yWorldBounds) setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom); }
	inline void zoomIn() { _zoom - 1 < 0 ? _zoom = 0 : _zoom--; _zoomGoal = _zoom; if (CAMERA_ASPECT_RATIO_X * _zoom < _xWorldBounds && CAMERA_ASPECT_RATIO_Y * _zoom < _yWorldBounds) setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom); }

	void shake(const float& intensity, const float& time);

	void fadeIn(const float& time);
	void fadeOut(const float& time);

	void update(const double& deltaTime);
	void render() const;
	void last_render() const;

	void setWorldBounds(const int& xBound, const int& yBound);
};