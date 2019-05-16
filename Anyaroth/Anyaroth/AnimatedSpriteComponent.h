#pragma once
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include <vector>

typedef unsigned int uint;

class GameObject;

struct AnimationStateImage
{
	uint name;
	uint numFrames;
	bool loop;
	bool animationFinished;
	uint lapse;
};

class AnimatedSpriteComponent : public SpriteComponent, public PhysicsComponent
{
private:
	GameObject* _obj = nullptr;
protected:
	vector<AnimationStateImage> _animations = {};

	uint _currentAnim = 0;
	uint _frame = 0;
	double _timer = 0.0;
	bool _animationFinished = false;

public:
	enum Player { Idle, Walk, WalkBack, MeleeKnife, MeleeSword, BeforeJump, Jump, StartFalling, Falling, Hurt, Dash, DashDown, DashBack, MeleeHalberd, PlayerDie };
	enum Enemy { EnemyIdle, EnemyWalk, EnemyAttack, EnemyDie };
	enum Capsule { CapsuleDrop, CapsuleSpawn };
	enum Gun { None, Shoot, NoAmmo, Reload };
	enum Bullet { Default, Destroy };
	enum MissileTurret { Deactivated, Activating, Active, Used };
	enum SingleAnim { Main };
	enum DoorAnim { Closed, Opened };
	enum Spenta {
		SpentaIdle, SpentaSwordLeft, SpentaSwordRight, SpentaStartShield, SpentaLoopShield, SpentaEndShield,
		SpentaDie, SpentaStartBomb, SpentaLoopBomb, SpentaEndBomb, SpentaOrb, SpentaWing
	};
	enum Azura {
		AzuraSpinEnd1, AzuraSpinEnd2, AzuraSpinEnd3, AzuraSpinLoop1, AzuraSpinLoop2, AzuraSpinLoop3, AzuraIdle1, AzuraIdle2, AzuraIdle3, AzuraWalk1, AzuraWalk2, AzuraWalk3,
		AzuraCannon1, AzuraCannon2, AzuraCannon3, AzuraJump, AzuraSpinStart1, AzuraSpinStart2, AzuraSpinStart3,
		AzuraScream1to2, AzuraScream2to3, AzuraDie
	};
	enum LaserContainer { LaserClosed, LaserClosing, LaserOpened, LaserOpening };
	enum Laser { LaserShooting, LaserWarning };
	enum Angra {
		AngraIdle, AngraWalk, AngraBH, AngraAppear, AngraDisappear, AngraRing, AngraDie1, AngraDie2
	};
	enum AngraSoldier {
		AngraSoldierIdle, AngraSoldierWalk, AngraSoldierWalkBack, AngraSoldierBeforeJump, AngraSoldierJump, AngraSoldierStartFalling, AngraSoldierFalling,
		AngraSoldierDash, AngraSoldierDashDown, AngraSoldierDashBack, AngraSoldierDie
	};
	enum FloatingHead {
		HeadIdle, HeadAttackStart, HeadAttackLoop, HeadAttackEnd, HeadDie
	};
	enum Throne {
		ThroneIdle, ThroneEnd1, ThroneEnd2
	};
	AnimatedSpriteComponent(GameObject* obj) : SpriteComponent(obj), PhysicsComponent(obj), RenderComponent(obj), Component(), _obj(obj) {}
	virtual ~AnimatedSpriteComponent() {}

	virtual void render(Camera* c) const;
	virtual void update(double deltaTime);

	void addAnim(uint name, uint numFrames, bool loop, uint lapse = 60);
	void playAnim(uint name);

	inline bool animationFinished() { return _animations[_currentAnim].animationFinished; }
	inline uint getCurrentAnim() const { return _currentAnim; }
	inline uint getCurrentFrame() const { return _frame; }
	inline bool isLooping() { return _animations[_currentAnim].loop; }

	void reset();
};