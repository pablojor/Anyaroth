#pragma once
#include "GameComponent.h"

class Camera : public GameComponent
{
	private:
		GameComponent * _followedObject = nullptr;
		SDL_Rect _cameraRect;

	public:
		Camera() {};
		Camera(GameComponent* followObject);
		Camera(SDL_Rect rect) : _cameraRect(rect) {};
		~Camera() {};

		SDL_Rect* getCameraRect() { return &_cameraRect; }

		void setCameraPosition(double x, double y);
		void setCameraSize(double w, double h);

		Vector2D getCameraPosition() { return Vector2D(_cameraRect.x, _cameraRect.y); }
		Vector2D getCameraSize() { return Vector2D(_cameraRect.w, _cameraRect.h); }

		void fixCameraToObject(GameComponent* object) { _followedObject = object; };
		void looseFixedObject();

		void update();
};

