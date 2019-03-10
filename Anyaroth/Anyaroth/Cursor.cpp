#include "Cursor.h"
#include "Texture.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "PlayState.h"
#include "Camera.h"

Cursor::Cursor(Texture* texture, Game* g, PlayState* play) : GameComponent(g)
{
	//Siempre primero los componentes que tienen que estar SI o SI.
	addComponent<Texture>(texture);

	//Resto de componentes
	_transform = addComponent<TransformComponent>();		//Como en el metodo anterior se ha creado este componente, imprime por pantalla que ya existe uno.
	_anim = addComponent<AnimatedSpriteComponent>();		//Como depende de Transform, en su constructura crea una si no ha encontrado Transform en el objeto.
	_anim->addAnim(AnimatedSpriteComponent::Idle, 1, false);

	_transform->setPosition({300, 200});

	_cam = play->getMainCamera();

	_anim->playAnim(AnimatedSpriteComponent::Idle);
}


Cursor::~Cursor()
{
}

void Cursor::update()
{
	GameComponent::update();

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
	

	return false;
}

Vector2D Cursor::getPosition()
{
	return _transform->getPosition();
}