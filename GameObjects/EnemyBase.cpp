#include "EnemyBase.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"
#include "Player.h"
#include "../../Engine/Utils/Utils.h"

#include "GameObjectWithAnimatedSprite.h"

EnemyBase::EnemyBase()
{
	m_pWeapon = NULL;
	m_EnemyDead = false;
	m_PointsForDeath = 0;
	m_VisionRange = 550;
	m_ShootRange = 400;
	m_MoveRangeX.x = 0;
	m_MoveRangeX.y = 0;
	m_MoveRangeY.x = 0;
	m_MoveRangeY.y = 0;
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialise()
{
	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
	m_CollisionType = E_Collider_Enemy;
	m_CurrentState = E_EnemyState_IDLE;

	m_targetLocation = (m_AnimatedSprite.getPosition());
}

void EnemyBase::Update()
{
	m_AnimatedSprite.Animate();

	if (m_pWeapon && m_pWeapon->GetWeaponAmmo() == 0)
	{
		this->Reload();
	}

	if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Death && m_AnimatedSprite.AnimationFinished())
	{
		this->KillEnemy();
	}

	//Update Enemy Particle Effects
	for (std::vector<GameObjectWithAnimatedSprite*>::iterator it = m_particleEffectList.begin(); it != m_particleEffectList.end();)
	{
		if ((*it)->AnimationFinished())
		{
			SAFE_DELETE_PTR((*it));
			it = m_particleEffectList.erase(it);
		}
		else
		{
			(*it)->Update((int)m_AnimatedSprite.getScale().x);
			it++;
		}
	}
}

void EnemyBase::GetPosition(int& x, int& y)
{
	x = (int)m_AnimatedSprite.getPosition().x;
	y = (int)m_AnimatedSprite.getPosition().y;
}

void EnemyBase::OnCollision(Collider2D* pCollider2D)
{	
	if (pCollider2D->GetCollisionType() == E_Collider_Bullet_Player)
	{
		Bullet* m_Bullet = (Bullet*)(pCollider2D);
		this->TakeDamage(m_Bullet->GetBulletDamage());
	}
}

void EnemyBase::SetTargetPosition(sf::Vector2f targetLocation)
{
	m_targetLocation = targetLocation;
}

bool EnemyBase::CanSeePlayer(sf::Vector2f targetPoint)
{
	sf::Vector2i currentPosition(0, 0);
	this->GetPosition(currentPosition.x, currentPosition.y);

	sf::Vector2f distanceVector = targetPoint - (sf::Vector2f)currentPosition;
	float distanceSquared = (distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);

	if (distanceSquared > (m_VisionRange * m_VisionRange))
		return false;
	else
		return true;
}

bool EnemyBase::CanShootPlayer(sf::Vector2f targetPoint)
{
	sf::Vector2i currentPosition(0, 0);
	this->GetPosition(currentPosition.x, currentPosition.y);

	sf::Vector2f distanceVector = targetPoint - (sf::Vector2f)currentPosition;
	float distanceSquared = (distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);

	if (distanceSquared > (m_ShootRange * m_ShootRange))
		return false;
	else
		return true;
}

int EnemyBase::GetPointsForDeath()
{
	return m_PointsForDeath;
}

void EnemyBase::Fire()
{
	if (m_pWeapon)
	{
		m_pWeapon->Fire(E_Collider_Bullet_Enemy);
	}
}

void EnemyBase::Reload()
{
	if (m_pWeapon)
	{
		m_pWeapon->Reload();
	}
}

bool EnemyBase::getReloadState()
{
	return m_reloading;
}

int EnemyBase::getWeaponAmmo()
{
	return m_pWeapon->GetWeaponAmmo();
}

int EnemyBase::getClipMax()
{
	return m_pWeapon->GetClipMax();
}

void EnemyBase::TakeDamage(int damage)
{
	m_Health -= damage;

	if (this->IsEnemyDead())
	{
		m_EnemyDead = true;
		SAFE_DELETE_PTR(m_pWeapon);
		AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
		pAudioManager->PlaySoundFX("sounds/sfx_turtle_death.wav");
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Death);
	}
}

void EnemyBase::KillEnemy()
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();
	Player* PlayerPtr = (Player*)pCurrentGameState->GetPlayer();
	pCurrentGameState->RemoveGameObject(this);

	PlayerPtr->AddPointsToScore(this->GetPointsForDeath());
}

bool EnemyBase::IsEnemyDead()
{
	if (m_Health <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool EnemyBase::AnimationFinished()
{
	if (m_AnimatedSprite.GetCurrentFrame() == 12)
	{
		return true;
	}
	else
	{
		return false;
	}
}