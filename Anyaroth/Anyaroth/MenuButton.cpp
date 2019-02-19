#include "MenuButton.h"
#include "TransformComponent.h"

MenuButton::MenuButton(Vector2D pos, double height, double width, Texture* texture, Game* g, callback* cb) : _pos(pos), _height(height), _width(width), g(g), cb(cb)
{
	addComponent<Texture>(texture);

	auto transform = addComponent<TransformComponent>();
	transform->setPosition(_pos.getX(), _pos.getY());
}

MenuButton::~MenuButton()
{
}

SDL_Rect MenuButton::getRect()
{
	SDL_Rect rect;
	rect.x = _pos.getX();
	rect.y = _pos.getY();
	rect.h = _height;
	rect.w = _width;
	return SDL_Rect();
}

void MenuButton::handleInput(const SDL_Event & event)
{
	GameComponent::handleInput(event);

	int x, y;
	SDL_GetMouseState(&x, &y);
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		SDL_Point point = { event.button.x, event.button.y };
		SDL_Rect rect = getRect();
		if (SDL_PointInRect(&point, &rect))
			cb(g);
	}
}