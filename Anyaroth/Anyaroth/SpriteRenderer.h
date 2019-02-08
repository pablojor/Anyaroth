#pragma once
#include "RenderComponent.h"
#include "GameComponent.h"

class SpriteRenderer : public RenderComponent {
private:
	Texture * texture = nullptr;
	unsigned int width = 0;
	unsigned int heigth = 0;
public:
	SpriteRenderer(GameComponent* _parent, Texture* _texture, unsigned int _width, unsigned int _heigth);
	~SpriteRenderer();
	void render() const;
};
