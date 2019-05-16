#pragma once
#include "UIElement.h"
#include <string>
#include "Vector2D.h"
#include "Texture.h"

class TextUI : public UIElement
{
protected:
	Font* _font = nullptr;
	uint _fontSize;
	string _text = "";
	SDL_Color _color;
	Texture* _texture = nullptr;

	SDL_Rect _destRect;
public:
	TextUI() : UIElement(nullptr), _texture(NULL) {}
	TextUI(Game* game);
	TextUI(Game* game, string text, Font* font, uint fontSize = 12, int xPos = 0, int yPos = 0, SDL_Color color = { 0, 0, 0, 255 });
	~TextUI() { if (_texture != nullptr) delete _texture; }

	virtual void render() const;
	virtual void update(double deltaTime) {}
	virtual bool handleEvent(const SDL_Event& event) { return false; }

	inline string getText() const { return _text; }
	void setText(string text);

	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setScale(float ratio);

	inline Vector2D getPosition() const { return Vector2D(_destRect.x, _destRect.y); }
	inline Vector2D getSize() const { return Vector2D(_destRect.w, _destRect.h); }

	void setFont(string fontName, uint fontSize);

	inline void setColor(const SDL_Color& color) { _color = color; }
	inline SDL_Color getColor() const { return _color; }

	inline int getW() const { return _destRect.w; }
	inline int getH() const { return _destRect.h; }
	inline int getX() const { return _destRect.x; }
	inline int getY() const { return _destRect.y; }
};