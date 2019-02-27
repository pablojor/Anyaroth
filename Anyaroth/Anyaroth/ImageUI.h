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
		ImageUI() {};
		ImageUI(Texture* image);
		~ImageUI() {};

		virtual void render() const;
		virtual void update() {}
		virtual void handleEvent(const SDL_Event& event) {}

		void setPosition(int x, int y);
		void setSize(int w, int h);
		void setClippingAreaSize(float w, float h);		//Solo el alto y ancho porque la posicion tiene que ser la misma (Valor de 0 a 1)
};

