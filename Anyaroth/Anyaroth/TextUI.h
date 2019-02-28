#pragma once
#include "UIElement.h"
#include <string>
#include "Vector2D.h"
#include "Texture.h"

class TextUI : public UIElement
{
	private:
		SDL_Rect _destRect;

	protected:
		Font* _font = nullptr;
		uint _fontSize;
		string _text = "";
		SDL_Color _color;

	public:
		TextUI() : UIElement(nullptr) {};
		TextUI(Game* game);
		TextUI(Game* game, string text, Font* font, uint fontSize = 12, SDL_Color color = { 0, 0, 0, 255});
		~TextUI() {};

		virtual void render() const;
		virtual void update() {};
		virtual void handleEvent(const SDL_Event& event) {};

		inline string getText() { return _text; }
		inline void setText(string text) { _text = text; }

		void setPosition(int x, int y);
		void setSize(int w, int h);
		Vector2D getPosition() { return Vector2D(_destRect.x, _destRect.y); }
		Vector2D getSize() { return Vector2D(_destRect.w, _destRect.h); }

		void setFont(string fontName, uint fontSize);
		
		inline void setColor(const SDL_Color& color) { _color = color; }
		inline SDL_Color getColor() { return _color; }

};

