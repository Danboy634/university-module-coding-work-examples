#include "EnemyTurtle3.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "../../Engine/Core/MathHelpers.h"
#include "../GameObjects/Player.h"

//Weapons
#include "../Weapons/SniperWeapon.h"

EnemyTurtle3::EnemyTurtle3()
{
}

EnemyTurtle3::~EnemyTurtle3()
{

}

void EnemyTurtle3::Initialise()
{
	m_Health = 25;
	m_PointsForDeath = 20;

	m_VisionRange = 700;
	m_ShootRange = 600;

	m_MoveRangeX.x = 2970;
	m_MoveRangeX.y = 1980;
	m_MoveRangeY.x = 185;
	m_MoveRangeY.y = 1925;

	float randTargetX = (float)(m_MoveRangeX.x + (rand() % (int)m_MoveRangeX.y));
	float randTargetY = (float)(m_MoveRangeY.x + (rand() % (int)m_MoveRangeY.y));
	m_AnimatedSprite.setPosition(randTargetX, randTargetY);

	m_pWeapon = new SniperWeapon();
	m_pWeapon->Initialise();

	GameDataManager* pGameDataManager = C_SysContext::Get <GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_turtle3.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Idle, pSpritesheetDef, "spr_turtle3_idle", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Walk, pSpritesheetDef, "spr_turtle3_walk", 10, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Precision, pSpritesheetDef, "spr_turtle3_precision", 10, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Death, pSpritesheetDef, "spr_turtle3_death", 10, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Hit, pSpritesheetDef, "spr_turtle3_hit", 10, false);
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);

	EnemyBase::Initialise();
}

void EnemyTurtle3::toIdleState()
{
	if (m_CurrentState == E_EnemyState_IDLE)
		return;

	m_CurrentState = E_EnemyState_IDLE;
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
}

void EnemyTurtle3::toWalkingState()
{
	if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Idle)
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
	}

	if (m_CurrentState == E_EnemyState_WALKING || m_CurrentState == E_EnemyState_ATTACKING || m_CurrentState == E_EnemyState_HIT)
		return;

	m_CurrentState = E_EnemyState_WALKING;
}

void EnemyTurtle3::toAttackingState()
{
	if (m_CurrentState == E_EnemyState_ATTACKING || m_CurrentState == E_EnemyState_HIT)
		return;

	m_CurrentState = E_EnemyState_ATTACKING;
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
	pAudioManager->PlaySoundFX("sounds/sfx_smg5.wav");
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
}

void EnemyTurtle3::Update()
{
	if (!m_EnemyDead)
	{
		if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Hit && m_AnimatedSprite.AnimationFinished())
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
		else if (m_CurrentState == E_EnemyState_IDLE)
		{
			int stayIdle = rand() % 200;

			if (stayIdle == 1)
			{
				float randTargetX = (float)m_MoveRangeX.x + (rand() % (int)m_MoveRangeX.y);
				float randTargetY = (float)m_MoveRangeY.x + (rand() % (int)m_MoveRangeY.y);

				SetTargetPosition(sf::Vector2f(randTargetX, randTargetY));
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

			if (m_CurrentState != E_EnemyState_ATTACKING || distance > 500)
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

void EnemyTurtle3::UpdateWeapon()
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

void EnemyTurtle3::GetPosition(int& x, int& y)
{
	EnemyBase::GetPosition(x, y);
}

void EnemyTurtle3::OnCollision(Collider2D * pCollider2D)
{
	if (pCollider2D->GetCollisionType() == E_Collider_Bullet_Player && m_AnimatedSprite.GetCurrentAnimation() != E_AnimationState_Death)
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Hit);
		m_CurrentState = E_EnemyState_HIT;

		GameObjectWithAnimatedSprite* particleEffectHit = new GameObjectWithAnimatedSprite();
		particleEffectHit->Initialise(0, "sprites/effects/spr_hit_heavy.xml", "spr_hit_heavy", 10, false, (int)m_AnimatedSprite.getPosition().x, (int)m_AnimatedSprite.getPosition().y);
		m_particleEffectList.push_back(particleEffectHit);

		EnemyBase::OnCollision(pCollider2D);
	}
}