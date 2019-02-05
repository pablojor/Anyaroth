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
	virtual void render(GameObject* o, Uint32 time) = 0;
};

#endif /* RENDERCOMPONENT_H_ */
