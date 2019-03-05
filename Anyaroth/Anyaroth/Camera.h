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
		Camera() {};
		Camera(GameComponent* followObject);
		Camera(SDL_Rect rect) : _cameraRect(rect) {};
		~Camera();

		SDL_Rect* getCameraRect() { return &_cameraRect; }

		void setCameraPosition(double x, double y);
		void setCameraSize(double w, double h);

		void setBackGround(BackGround* bg) { _backGround = bg; }

		Vector2D getCameraPosition() { return Vector2D(_cameraRect.x, _cameraRect.y); }
		Vector2D getCameraSize() { return Vector2D(_cameraRect.w, _cameraRect.h); }

		void fixCameraToObject(GameComponent* object) { _followedObject = object; };
		void looseFixedObject();

		GameComponent* getFollowedObject() { return _followedObject; };

		void update();
		void render() const;
};

