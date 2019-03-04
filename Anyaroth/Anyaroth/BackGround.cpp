#include "BackGround.h"
#include "Camera.h"

BackGround::BackGround(Texture * texture, Camera * camera) : _texture(texture)
{
	_mainRect = { 0, 0, camera->getCameraRect()->w, camera->getCameraRect()->h };
}

void BackGround::render() const
{
	_texture->render(_mainRect);
}
