#include "BackGround.h"
#include "Camera.h"
#include "Game.h"


BackGround::BackGround(Texture * texture, Camera * camera) : _texture(texture)
{
	_mainRect = { 0, 0, camera->getCameraRect()->w, camera->getCameraRect()->h };
}

void BackGround::render() const
{
	SDL_Rect destRect = {	_mainRect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X ,_mainRect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y ,
							_mainRect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, _mainRect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

	_texture->render(destRect);
}