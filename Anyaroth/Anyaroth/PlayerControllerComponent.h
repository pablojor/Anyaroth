#pragma once
#include "InputComponent.h"
#include "MovingComponent.h"
#include "AnimatedSpriteComponent.h"
#include "FollowingComponent.h"

class GameComponent;

class PlayerControllerComponent : public InputComponent
{
private:
	AnimatedSpriteComponent* _anim;
	GameComponent* _obj;
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

	

	inline bool IsSpaceDown() {return _spacePul;}
	inline bool currYDir() { return _spacePul; }
	inline bool currXDir() { if (_aPul)return -1; else if (_dPul) return 1; else 0; }
	inline bool isAttacking() { return _isAttacking; }
	inline void setIsAttacking(bool b) { _isAttacking = b; }
	inline void newDash() { _amountOfDash++; }
	inline int amountDash() { return _amountOfDash; }

	inline bool isReloading() { return _isReloading; };
	inline void setIsReloading(bool b) { _isReloading = b; };

	void reload();

};