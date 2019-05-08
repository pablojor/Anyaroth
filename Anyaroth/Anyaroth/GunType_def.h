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
	BHCannon_Weapon,

	BomberGun_Weapon,
	BasicEnemyGun_Weapon,
	BasicEnemyShotgun_Weapon,
	BossOrbCanon_Weapon,
	None = 100
};

enum MeleeType
{
	Knife_Weapon,
	Sword_Weapon,
	PoleAxe_Weapon,

	BossSword_Weapon,
	BossPoleAxe_Weapon
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
	PlayerImprovedShotgunArmType,
	PlayerPistolArmType,
	PlayerRifleArmType,
	PlayerImprovedRifleArmType,
	PlayerBounceCannonArmType,
	PlayerSniperArmType,
	PlayerBHCannonArmType,
	TurretArmType,
	TrooperArmType
};