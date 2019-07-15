#ifndef BULLET_H
#define BULLET_H

#include "../../Engine/Core/GameObject.h"
#include "../GameData/SpritesheetDef.h"
#include "../../Engine/Physics/BoxCollider2D.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Game/Weapons/BlitzWeapon.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Game/Weapons/WeaponBase.h"

class Bullet : public GameObject, public BoxCollider2D
{
public:
	Bullet();
	virtual ~Bullet();

	virtual void Initialise();
	virtual void Initialise(int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, int fps, bool loop, float velocity, int damage, int friendlyFire);
	virtual void Update();
	virtual void GetPosition(int& x, int& y);
	virtual void OnCollision(Collider2D* pCollider2D);
	void OnCollision(TileMap* pCollider2D);

	void SetPosition(int x, int y);
	void SetRotation(float angle);
	void SetScale(float scaleX, float scaleY);

	int GetBulletDamage();

private:
	float m_Velocity;
	float m_Lifetime;
	int m_damageModifier;

	AnimatedSprite m_AnimatedSprite;
};

#endif
