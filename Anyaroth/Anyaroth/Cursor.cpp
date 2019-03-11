#include "Cursor.h"
#include "Texture.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PlayState.h"
#include "Camera.h"

Cursor::Cursor(Texture* texture, Game* g, PlayState* play) : GameComponent(g)
{
	addComponent<Texture>(texture);

	_transform = addComponent<TransformComponent>();
	_anim = addComponent<AnimatedSpriteComponent>();
	_anim->addAnim(AnimatedSpriteComponent::Idle, 1, false);

	_cam = play->getMainCamera();

	_anim->playAnim(AnimatedSpriteComponent::Idle);
}

void Cursor::update(double time)
{
	GameComponent::update(time);

	_mouseX += (_cam->getCameraPosition().getX() - _prevCamPos.getX());
	_mouseY += (_cam->getCameraPosition().getY() - _prevCamPos.getY());
	_prevCamPos = _cam->getCameraPosition();

	_transform->setPosition(_mouseX - _anim->getTexture()->getW() / 2, _mouseY - _anim->getTexture()->getH() / 2);
}

bool Cursor::handleInput(const SDL_Event& event)
{
	//si se mueve el raton, se actualiza
	if (event.type == SDL_MOUSEMOTION)
	{
		_prevCamPos = _cam->getCameraPosition();
		_mouseX = event.motion.x + _prevCamPos.getX();
		_mouseY = event.motion.y + _prevCamPos.getY();
		return true;
	}
	else
		_movingMouse = false;

	return false;
}

Vector2D Cursor::getPosition()
{
	return _transform->getPosition();
}