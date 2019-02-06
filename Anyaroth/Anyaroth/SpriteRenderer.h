#pragma once
#include "RenderComponent.h"
#include "GameComponent.h"
#include "Transform.h"

class SpriteRenderer : public RenderComponent {
private:
	Texture * texture = nullptr;
	unsigned int width = 0;
	unsigned int heigth = 0;
	Transform* transform;
public:
	SpriteRenderer(Transform* trans, Texture* _texture, unsigned int _width, unsigned int _heigth);
	~SpriteRenderer();
	void render() const;
};
