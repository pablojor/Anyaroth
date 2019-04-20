#pragma once

enum GunType
{
	Pistol_Weapon,
	BasicShotgun_Weapon,
	ImprovedShotgun_Weapon,
	BasicRifle_Weapon,
	ImprovedRifle_Weapon,
	PlasmaSniper_Weapon,
	BounceOrbCannon_Weapon,
	GravityBombCannon_Weapon,

	BomberGun_Weapon,
	BasicEnemyGun_Weapon,
	BasicEnemyShotgun_Weapon,
	BossOrbCanon_Weapon
};

enum MeleeType
{
	Knife_Weapon,
	Axe_Weapon,
	Lightsaber_Weapon,
	Chainsaw_Weapon
};

enum BulletAnimType
{
	Default,
	RifleBullet,
	ShotGunBullet,
	TurretBullet,
	SpentaBomb,
	SpentaOrb,
	BHBullet,
	SniperBullet
};

enum ArmAnimType
{
	DefaultArmType,
	PlayerShotgunArmType,
	PlayerPistolArmType,
	PlayerRifleArmType,
	PlayerBounceCannonArmType,
	PlayerSniperArmType,
	TurretArmType,
	BHCannonArmType
};