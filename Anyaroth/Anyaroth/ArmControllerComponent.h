#pragma once

#include "InputComponent.h"
#include "TransformComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"
#include "Cursor.h"

class GameComponent;
class PlayerArm;

class ArmControllerComponent : public InputComponent
{
private:
	FollowingComponent* _followC;
	GameComponent* _player;
	PlayerArm* _obj;
	AnimatedSpriteComponent* _anim;
	TransformComponent* _transform = nullptr;
	bool _leftClickPul = false, _canShoot = true;
	bool _rPul = false;

	bool isReloading = false;


	bool _shootInput = false;

	/*bool _mouseIsMoving = false;
	Vector2D _lastCamPos;
	*/
	TransformComponent* _cursorTC = nullptr;
	bool _flipShot = false;

public:
	ArmControllerComponent(GameComponent* obj);
	virtual void handleInput(const SDL_Event& event);

	int mouseX = 0; int mouseY = 0;
	int flipPosOffset = 8; //Distancia que se mueve el brazo al hacer flip
	void setCursorTC(Cursor* cursor) { _cursorTC = cursor->getComponent<TransformComponent>(); };

	bool isShooting() { return _shootInput; };
	void setShooting(bool s) { _shootInput = s; };
	bool shootButton() { return _leftClickPul && _canShoot; };
	bool flipShooting() { return _flipShot; };
	void toggleCanShoot() { _canShoot = false; _flipShot = false; };
};

