#pragma once
#include "GameComponent.h"
class Camera : public GameComponent
{
	private:
		SDL_Rect _cameraRect;
	public:
		Camera() {};
		Camera(GameComponent* followObject);
		Camera(SDL_Rect rect) : _cameraRect(rect) {};
		~Camera() {};

		void setCameraRect(SDL_Rect rect) { _cameraRect = rect; }
		SDL_Rect* getCameraRect() { return &_cameraRect; }

		void setCameraPosition(double x, double y);
		void setCameraSize(double w, double h);

		Vector2D getCameraPosition();
		Vector2D getCameraSize();

		void fixCameraToObject(GameComponent* object);
		void looseFixedObject();
};

