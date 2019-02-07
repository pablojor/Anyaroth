#ifndef RENDERCOMPONENT_H_
#define RENDERCOMPONENT_H_

#include "GameObject.h"

/*
 *
 */
class RenderComponent {
public:
	RenderComponent();
	virtual ~RenderComponent();
	virtual void render(/*GameObject* o, Uint32 time*/) const = 0;
	virtual void renderFrame(int fil, int col) const = 0;
};

#endif /* RENDERCOMPONENT_H_ */