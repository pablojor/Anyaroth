#pragma once
#include "UIElement.h"
#include "Texture.h"

class ImageUI :	public UIElement
{
private:
	Texture * _image;
	SDL_Rect destRect;
	SDL_Rect clipArea;
public:
	ImageUI(Texture* image);
	~ImageUI() {};

	virtual void render() const;

	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setClippingArea(int w, int h);		//Solo el alto y ancho porque la posicion tiene que ser la misma
};

