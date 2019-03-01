#pragma once
#include "UIElement.h"
#include "Texture.h"

class ImageUI :	public UIElement
{
	protected:
		Texture* _image;
		SDL_Rect _destRect;
		SDL_Rect _clipArea;
	public:
		ImageUI() : UIElement(nullptr) {};
		ImageUI(Game* game, Texture* image, int xPos = 0, int yPos = 0);
		~ImageUI() {};

		virtual void render() const;
		virtual void update() {}
		virtual void handleEvent(const SDL_Event& event) {}

		void setPosition(int x, int y);
		void setSize(int w, int h);
		void setClippingAreaSize(float w, float h);		//Solo el alto y ancho porque la posicion tiene que ser la misma (Valor de 0 a 1)

		inline int getW() { return _destRect.w; };
		inline int getH() { return _destRect.h; };
		inline int getX() { return _destRect.x; };
		inline int getY() { return _destRect.y; };
};

