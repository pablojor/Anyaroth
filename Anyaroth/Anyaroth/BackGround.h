#pragma once
#include "Texture.h"
#include <utility>

class Camera;

class BackGround
{
protected:
	Texture* _texture = nullptr;
	SDL_Rect _mainRect;

public:
	BackGround(Texture* texture, Camera* camera);
	virtual ~BackGround() {}

	virtual void render() const;
	virtual void update(double deltaTime) {}

	virtual bool checkCameraStatus(pair<bool, int> status) { return false; }
};