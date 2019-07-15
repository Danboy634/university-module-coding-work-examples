#ifndef _ENEMY_BOSS_H
#define _ENEMY_BOSS_H

#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Game/GameData/GameDataManager.h"
#include "EnemyBase.h"

class EnemyBoss
	: public EnemyBase
{
public:
	EnemyBoss();
	virtual ~EnemyBoss();

	virtual void Initialise();
	virtual void Update();
	virtual void GetPosition(int& x, int& y);

	virtual void OnCollision(Collider2D* pCollider2D);

	void SetBossStats(int posX, int posY, int health, int maxInClip, float fireRate, float bulletSpeed, int bulletDamage);

	void toIdleState();
	void toWalkingState();
	void toAttackingState();

	bool IsBossDead();

private:
	enum E_AnimationState
	{
		E_AnimationState_Idle,
		E_AnimationState_Walk,
		E_AnimationState_Precision,
		E_AnimationState_Death,
		E_AnimationState_Hit,
		E_AnimationState_Egg_Idle,
		E_AnimationState_Egg_Crack,
		E_AnimationState_Egg_Start,
	};

	void UpdateWeapon();
};

#endif