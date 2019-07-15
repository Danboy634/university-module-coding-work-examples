#include "EnemyBoss.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/MathHelpers.h"
#include "../GameObjects/Player.h"

//Weapons
#include "../Weapons/BossWeapon.h"

EnemyBoss::EnemyBoss()
{
}

EnemyBoss::~EnemyBoss()
{

}

void EnemyBoss::Initialise()
{
	m_Health = 500;
	m_PointsForDeath = 500;

	m_VisionRange = 1200;
	m_ShootRange = 700;

	m_pWeapon = new BossWeapon();
	m_pWeapon->Initialise();

	GameDataManager* pGameDataManager = C_SysContext::Get <GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_boss.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Idle, pSpritesheetDef, "spr_boss_idle", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Walk, pSpritesheetDef, "spr_boss_walk", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Precision, pSpritesheetDef, "spr_boss_death", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Death, pSpritesheetDef, "spr_boss_death", 9, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Hit, pSpritesheetDef, "spr_boss_hit", 10, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Egg_Idle, pSpritesheetDef, "spr_boss_egg_idle", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Egg_Crack, pSpritesheetDef, "spr_boss_egg_crack", 10, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Egg_Start, pSpritesheetDef, "spr_boss_egg_start", 10, true);
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Egg_Start);
}

void EnemyBoss::SetBossStats(int posX, int posY, int health, int maxInClip, float fireRate, float bulletSpeed, int bulletDamage)
{
	m_AnimatedSprite.setPosition((float)posX, (float)posY);
	m_targetLocation = m_AnimatedSprite.getPosition();

	m_Health = health;

	m_pWeapon->ChangeWeaponStats(maxInClip, fireRate, bulletSpeed, bulletDamage);
}

void EnemyBoss::toIdleState()
{
	if (m_CurrentState == E_EnemyState_IDLE)
		return;

	m_CurrentState = E_EnemyState_IDLE;
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
}

void EnemyBoss::toWalkingState()
{
	if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Idle)
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
	}

	if (m_CurrentState == E_EnemyState_WALKING || m_CurrentState == E_EnemyState_ATTACKING || m_CurrentState == E_EnemyState_HIT)
		return;

	m_CurrentState = E_EnemyState_WALKING;
}

void EnemyBoss::toAttackingState()
{
	if (m_CurrentState == E_EnemyState_ATTACKING)
		return;

	m_CurrentState = E_EnemyState_ATTACKING;
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->PlaySoundFX("sounds/sfx_plasma1.wav");
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
}

void EnemyBoss::Update()
{
	if (!m_EnemyDead)
	{
		if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Egg_Start)
		{
			m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
			return;
		}
		else if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Egg_Crack)
		{
			EnemyBase::Update();
			if (m_AnimatedSprite.AnimationFinished())
			{
				toIdleState();
			}
			else
			{
				m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
				return;
			}
		}
		else if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Hit && m_AnimatedSprite.AnimationFinished())
		{
			toIdleState();
		}

		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();
		//get the player object and calculate it's position to check if the enemy can see/shoot the player
		GameObject* pPlayerObject = pGameState->GetPlayer();

		int targetX = 0;
		int targetY = 0;
		pPlayerObject->GetPosition(targetX, targetY);
		sf::Vector2f targetVector((float)targetX, (float)targetY);

		if (this->CanShootPlayer(targetVector))
		{
			toAttackingState();
			SetTargetPosition(targetVector);
		}
		else if (this->CanSeePlayer(targetVector))
		{
			toWalkingState();
			SetTargetPosition(targetVector);
		}

		if (m_CurrentState == E_EnemyState_ATTACKING)
		{
			targetVector.x -= m_AnimatedSprite.getPosition().x;
			targetVector.y -= m_AnimatedSprite.getPosition().y;

			targetVector = MathHelpers::Normalise(targetVector);

			if (CanShootPlayer(sf::Vector2f((float)targetX, (float)targetY)))
			{
				//use two vectors, one based on the player position, to calculate the angle to aim the weapon in order to hit the player
				sf::Vector2f up(0.f, -1.0f);
				sf::Vector2f forwards(targetVector.x, targetVector.y);

				float angle = 0.0f;
				angle = (MathHelpers::AngleBetweenVectors(up, forwards)) - 90;

				if (m_AnimatedSprite.getPosition().x > targetX)
				{
					angle = -angle;
				}

				m_pWeapon->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);
				m_pWeapon->SetRotation(angle);

				this->Fire();
			}
		}

		//get NPC's current location, calculate distance between location and target position
		sf::Vector2f currentPosition = m_AnimatedSprite.getPosition();
		sf::Vector2f faceDirection = m_targetLocation - currentPosition;
		float distance = sqrt(faceDirection.x * faceDirection.x + faceDirection.y * faceDirection.y);

		if (distance < 3)
		{
			toIdleState();
		}
		else
		{
			float angle = atan2(faceDirection.y, faceDirection.x);

			sf::Vector2f moveVector = sf::Vector2f(cos(angle), sin(angle));
			moveVector = moveVector * 2.f;

			if (m_CurrentState != E_EnemyState_ATTACKING || distance > 300)
			{
				m_AnimatedSprite.move(moveVector);
				toWalkingState();
			}
			else
			{
				m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
			}
		}

		//change the scale based on the direction the enemy is walking
		if (m_AnimatedSprite.getPosition().x > m_targetLocation.x)
		{
			m_AnimatedSprite.setScale(-1.f, 1.f);
		}
		else
		{
			m_AnimatedSprite.setScale(1.f, 1.f);
		}

		UpdateWeapon();

		m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
	}

	EnemyBase::Update();
}

void EnemyBoss::UpdateWeapon()
{
	if (m_pWeapon)
	{
		float weaponOffsetX = 0.f;
		float weaponOffsetY = 0.f;
		m_pWeapon->GetWeaponOffset(weaponOffsetX, weaponOffsetY);

		m_pWeapon->SetPosition(m_AnimatedSprite.getPosition().x + weaponOffsetX * m_AnimatedSprite.getScale().x,
			m_AnimatedSprite.getPosition().y + weaponOffsetY * m_AnimatedSprite.getScale().y);

		m_pWeapon->Update();
	}
}

void EnemyBoss::GetPosition(int& x, int& y)
{
	EnemyBase::GetPosition(x, y);
}

void EnemyBoss::OnCollision(Collider2D * pCollider2D)
{
	if (pCollider2D->GetCollisionType() == E_Collider_Bullet_Player && m_AnimatedSprite.GetCurrentAnimation() != E_AnimationState_Death)
	{
		if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Egg_Start)
		{
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Egg_Crack);
			return;
		}
		else if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Egg_Crack)
		{
			return;
		}

		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Hit);
		m_CurrentState = E_EnemyState_HIT;

		GameObjectWithAnimatedSprite* particleEffectHit = new GameObjectWithAnimatedSprite();
		particleEffectHit->Initialise(0, "sprites/effects/spr_hit_heavy.xml", "spr_hit_heavy", 10, false, (int)m_AnimatedSprite.getPosition().x, (int)m_AnimatedSprite.getPosition().y);
		m_particleEffectList.push_back(particleEffectHit);

		EnemyBase::OnCollision(pCollider2D);
	}
}

bool EnemyBoss::IsBossDead()
{
	return m_EnemyDead;
}