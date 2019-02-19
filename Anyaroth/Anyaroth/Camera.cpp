#include "Camera.h"
#include "CameraBehaivourComponent.h"

Camera::Camera(GameComponent * followObject)
{
	auto fc = addComponent<CameraBehaivourComponent>();
	fc->setFollowedObject(followObject);
}

void Camera::setCameraPosition(double x, double y)
{
	_cameraRect.x = x;
	_cameraRect.y = y;
}

void Camera::setCameraSize(double w, double h)
{
	_cameraRect.w = w;
	_cameraRect.h = h;
}

void Camera::fixCameraToObject(GameComponent * object)
{
	auto a = getComponent<CameraBehaivourComponent>();
	if (a == nullptr)
	{
		auto b = addComponent<CameraBehaivourComponent>();
		b->setFollowedObject(object);
	}
	else
		a->setFollowedObject(object);
}

void Camera::looseFixedObject()
{
	auto a = getComponent<CameraBehaivourComponent>();
	if (a != nullptr)
		a->looseFollowedObject();

}
