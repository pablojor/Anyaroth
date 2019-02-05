#ifndef INPUTCOMPONENT_H_
#define INPUTCOMPONENT_H_

#include "GameObject.h"

/*
 *
 */
class InputComponent {
public:
	InputComponent();
	virtual ~InputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event) = 0;
};

#endif /* INPUTCOMPONENT_H_ */
