#include "MenuButton.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

MenuButton::MenuButton(Vector2D pos, Texture* texture, Game* g, callback* cb) : _pos(pos), _texture(texture), g(g), cb(cb)
{
	addComponent<Texture>(_texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(_pos.getX(), _pos.getY());
	transform->setScale(BUTTON_SCALE);

	addComponent<SpriteComponent>();
}

SDL_Rect MenuButton::getRect() const
{
	SDL_Rect rect;
	rect.x = _pos.getX();
	rect.y = _pos.getY();
	rect.h = _texture->getH()*BUTTON_SCALE;
	rect.w = _texture->getW()*BUTTON_SCALE;
	SDL_Rect winRect = { rect.x * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X ,rect.y * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y ,
		rect.w * GAME_RESOLUTION_X / CAMERA_RESOLUTION_X, rect.h * GAME_RESOLUTION_Y / CAMERA_RESOLUTION_Y };

	return winRect;
}

bool MenuButton::handleInput(const SDL_Event & event)
{
	GameComponent::handleInput(event);
	bool handled = false;

	int x, y;
	SDL_GetMouseState(&x, &y);
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point point = { event.button.x, event.button.y };
		SDL_Rect rect = getRect();

		if (SDL_PointInRect(&point, &rect))
		{
			cb(g);
			handled = true;
		}
	}
	return handled;
}