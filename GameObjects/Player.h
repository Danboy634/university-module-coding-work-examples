#ifndef _PLAYER_H
#define _PLAYER_H

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Game/Weapons/WeaponBase.h"
#include "../../Engine/Utils/Utils.h" 
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Game/GameObjects/EnemyBase.h"

#include "SFML/Graphics.hpp"

class Player :	public GameObject, public BoxCollider2D
{
public:
	Player();
	virtual ~Player();

	//---GAME OBJECT INTERFACE IMPLEMENTATION
	virtual void Initialise() override;
	virtual void Update()override;
	virtual void GetPosition(int& x, int& y)override;

	//---BOX COLLIDER INTERFACE IMPLEMENTATION--------------------
	virtual void OnCollision(Collider2D* pCollider2D)override;
	virtual void OnCollision(TileMap* pCollider2D)override;

	//---------PUBLIC MEMBER FUNCTION----------------------------
	void Initialise(int fps, int posX, int posY);
	void Fire();
	void Reload();

	bool getReloadState();
	void hasReloaded();

	int getWeaponAmmo();
	int getAmmoInBag();
	void setAmmoInBag(int ammoValue);
	int getClipMax();
	int getCurrentWeapon();
	
	int getCurrentScore();
	void AddPointsToScore(int points);
	void LosePointsFromScore(int points);

	int getCurrentHealth();
	void LoseHealth(int value);
	void GainHealth(int value);
	bool IsPlayerDead();
	void KillPlayer();
	bool GameOver();

	void GetCollidePosition(int& x, int& y);

	bool musicIsPlaying;

private:
	void UpdateWeapon();

	AnimatedSprite m_AnimatedSprite;

	int m_PrevPositionX;
	int m_PrevPositionY;

	bool m_reloading;
	bool isReloaded;

	int m_CurrentWeapon;

	std::vector<WeaponBase*> m_pWeaponList;
	WeaponBase* m_pWeapon;

	int m_PlayerScore;
	int m_PlayerHealth;

	bool playerDead;
	bool gameOver;

	enum E_AnimationState
	{
		E_AnimationState_Idle,
		E_AnimationState_Walk,
		E_AnimationState_Sprint,
		E_AnimationState_Death,
		E_AnimationState_Dig,
		E_AnimationState_Hit,
		E_AnimationState_Holo,
		E_AnimationState_Melee,
		E_AnimationState_Dash,
		E_AnimationState_teleportIn,
		E_AnimationState_teleportOut
	};
};

#endif
