#pragma once
#include "InputComponent.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"
//#include "Cursor.h"

class GameComponent;
class PlayerArm;

class ArmControllerComponent : public InputComponent
{
private:
	FollowingComponent* _followC = nullptr;
	GameComponent* _player = nullptr;
	PlayerArm* _obj = nullptr;
	AnimatedSpriteComponent* _anim = nullptr;
	TransformComponent* _transform = nullptr;
	TransformComponent* _cursorTC = nullptr;
	bool _leftClickPul = false, _canShoot = true, _rPul = false, isReloading = false;

public:
	ArmControllerComponent(GameComponent* obj);
	virtual void handleInput(const SDL_Event& event);

	int mouseX = 0; int mouseY = 0;
	int flipPosOffset = 8; //Distancia que se mueve el brazo al hacer flip
	//inline void setCursorTC(Cursor* cursor) { _cursorTC = cursor->getComponent<TransformComponent>(); }
};