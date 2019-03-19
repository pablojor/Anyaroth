#include "BackGround.h"
#include "Camera.h"
#include "Game.h"


BackGround::BackGround(Texture * texture, Camera * camera) : _texture(texture)
{
	_mainRect = { 0, 0, GAME_RESOLUTION_X, GAME_RESOLUTION_Y };
}

void BackGround::render() const
{
	_texture->render(_mainRect);
}