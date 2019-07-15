#ifndef _ENEMY_DUCK_2_H
#define _ENEMY_DUCK_2_H

#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Core/GameObject.h"
#include "../../Game/GameData/GameDataManager.h"
#include "EnemyBase.h"

class EnemyDuck2
	: public EnemyBase
{
public:
	EnemyDuck2();
	virtual ~EnemyDuck2();

	virtual void Initialise();
	virtual void Update();
	virtual void GetPosition(int& x, int& y);

	virtual void OnCollision(Collider2D* pCollider2D);

	void toIdleState();
	void toWalkingState();
	void toAttackingState();

private:
	enum E_AnimationState
	{
		E_AnimationState_Idle,
		E_AnimationState_Walk,
		E_AnimationState_Precision,
		E_AnimationState_Death,
		E_AnimationState_Hit
	};

	void UpdateWeapon();
};

#endif