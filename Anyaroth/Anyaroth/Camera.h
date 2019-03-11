#pragma once
#include "GameComponent.h"
#include "BackGround.h"
#include <utility>

class Camera
{
private:
	GameComponent * _followedObject = nullptr;
	SDL_Rect _cameraRect;
	BackGround* _backGround = nullptr;

	void moveCamera();

	pair<bool, int> _cameraStatus = pair<bool, int>(false, 0);

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

	void update(double time);
	void render() const;
};