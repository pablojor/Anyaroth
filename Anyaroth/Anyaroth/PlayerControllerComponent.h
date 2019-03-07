#pragma once
#include "InputComponent.h"
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"

class GameComponent;

class PlayerControllerComponent : public InputComponent
{
private:
	AnimatedSpriteComponent* _anim = nullptr;
	GameComponent* _obj = nullptr;
	MovingComponent* _movement = nullptr;
	bool _spacePul = false, _aPul = false, _sPul = false, _dPul = false, _sfPul = false;
	bool _rightClickPul = false, _isAttacking = false;
	bool _isReloading = false, _rPul = false, _isSwapping = false, _qPul = false;
	bool _jumping = false, _dashing = false;

	int _amountOfDash = 2;

public:
	PlayerControllerComponent(GameComponent* obj);
	virtual void handleInput(const SDL_Event& event);

	void changeJump();
	void ableJump();

	inline bool IsSpaceDown() const {return _spacePul;}
	inline bool currYDir() const { return _spacePul; }
	inline bool currXDir() const { if (_aPul) return -1; else if (_dPul) return 1; else return 0; }
	inline bool isAttacking() const { return _isAttacking; }
	inline void setIsAttacking(bool b) { _isAttacking = b; }
	inline void newDash() { _amountOfDash++; }
	inline int amountDash() const { return _amountOfDash; }

	inline bool isReloading() const { return _isReloading; }
	inline void setIsReloading(bool b) { _isReloading = b; }

	void reload();
};