#pragma once
#include "GameComponent.h"
#include "BackGround.h"
#include <utility>

//Valores predeterminados
const int CAMERA_ASPECT_RATIO_X = 16;
const int CAMERA_ASPECT_RATIO_Y = 9;
const int CAMERA_SCALE_FACTOR = 30;
const int CAMERA_RESOLUTION_X = CAMERA_ASPECT_RATIO_X * CAMERA_SCALE_FACTOR;
const int CAMERA_RESOLUTION_Y = CAMERA_ASPECT_RATIO_Y * CAMERA_SCALE_FACTOR;


class Camera
{
private:
	GameComponent * _followedObject = nullptr;
	SDL_Rect _cameraRect;
	BackGround* _backGround = nullptr;

	void moveCamera();
	void smoothCameraZoom(const double& time);

	pair<bool, int> _cameraStatus = pair<bool, int>(false, 0);
	int _zoom = CAMERA_SCALE_FACTOR; int _zoomGoal = CAMERA_SCALE_FACTOR;

public:
	Camera() {}
	Camera(GameComponent* followObject);
	Camera(SDL_Rect rect) : _cameraRect(rect) {}
	~Camera();

	inline SDL_Rect* getCameraRect() { return &_cameraRect; }

	void setCameraPosition(double x, double y);
	void setCameraSize(double w, double h);

	inline void setBackGround(BackGround* bg) { _backGround = bg; }

	inline Vector2D getCameraPosition() const { return Vector2D(_cameraRect.x, _cameraRect.y); }
	inline Vector2D getCameraSize() const { return Vector2D(_cameraRect.w, _cameraRect.h); }

	inline bool inCamera(const Vector2D& pos) const { return (pos.getX() > _cameraRect.x && pos.getX() < _cameraRect.x + _cameraRect.w && pos.getY() > _cameraRect.y && pos.getY() < _cameraRect.y + _cameraRect.h); }

	void fixCameraToObject(GameComponent* object) { _followedObject = object; };
	void looseFixedObject();

	inline GameComponent* getFollowedObject() const { return _followedObject; };

	void setZoom(const float& zoomRatio, const bool& smoothZoom = false);
	inline float getZoom() const { return _zoom; }
	inline void zoomOut() { _zoom++; _zoomGoal = _zoom; setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom); }
	inline void zoomIn() { _zoom--; _zoomGoal = _zoom; setCameraSize(CAMERA_ASPECT_RATIO_X * _zoom, CAMERA_ASPECT_RATIO_Y * _zoom);	}

	void update(const double& time);
	void render() const;
};