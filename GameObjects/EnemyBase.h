#ifndef  _ENEMY_BASE_H
#define _ENEMY_BASE_H

#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Core/GameObject.h"
#include "../GameData/GameDataManager.h"
#include "../Weapons/WeaponBase.h"
#include "Bullet.h"
#include "GameObjectWithAnimatedSprite.h"

#include <random>

class EnemyBase :
	public GameObject, public BoxCollider2D
{
public:

	EnemyBase();
	virtual ~EnemyBase() = 0;

	virtual void Initialise();
	virtual void Update();
	virtual void GetPosition(int& x, int& y);

	virtual void OnCollision(Collider2D* pCollider2D);

	void SetTargetPosition(sf::Vector2f targetLocation);

	bool CanSeePlayer(sf::Vector2f targetPoint);
	bool CanShootPlayer(sf::Vector2f targetPoint);

	int GetPointsForDeath();

	bool AnimationFinished();

protected:
	void Fire();
	void Reload();
	bool getReloadState();
	int getWeaponAmmo();
	int getClipMax();

	bool m_reloading;

	void TakeDamage(int damage);
	bool IsEnemyDead();
	void KillEnemy();

	AnimatedSprite m_AnimatedSprite;
	int m_Health;

	int m_PointsForDeath;

	WeaponBase* m_pWeapon;

	enum EnemyState {
		E_EnemyState_IDLE,
		E_EnemyState_WALKING,
		E_EnemyState_HIT,
		E_EnemyState_ATTACKING
	};

	int m_CurrentState;

	int m_VisionRange;
	int m_ShootRange;
	sf::Vector2f m_targetLocation;
	
	sf::Vector2f m_MoveRangeX;
	sf::Vector2f m_MoveRangeY;

	bool m_EnemyDead;

	std::vector<GameObjectWithAnimatedSprite*> m_particleEffectList;

private:
	enum E_AnimationState
	{
		E_AnimationState_Idle,
		E_AnimationState_Walk,
		E_AnimationState_Precision,
		E_AnimationState_Death,
		E_AnimationState_Hit
	};
};
#endif