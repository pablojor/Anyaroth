#pragma once
#include "PhysicsComponent.h"

class GameComponent;
struct SDL_Rect;

class CameraBehaivourComponent : public PhysicsComponent
{
	private:
		GameComponent * _followedObject = nullptr;
		SDL_Rect* _cameraRectRef;

	public:
		CameraBehaivourComponent(GameComponent* obj);
		~CameraBehaivourComponent() {};

		void setFollowedObject(GameComponent* object) { _followedObject = object; };
		void looseFollowedObject();

		virtual void update();
};

