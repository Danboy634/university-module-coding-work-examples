#include "Bullet.h"
#include "EnemyBase.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	
}

void Bullet::Initialise()
{
}

void Bullet::Initialise(int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, int fps, bool loop, float velocity, int damage, int friendlyFire)
{
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(animationId, pSpritesheetDef, animationName, fps, loop);
	m_AnimatedSprite.SetCurrentAnimation(animationId);

	m_damageModifier = damage;
	m_Velocity = velocity;
	m_Lifetime = 1.f;

	Bullet::Update();
	m_CollisionType = friendlyFire;
}

void Bullet::Update()
{
	m_AnimatedSprite.Animate();
	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();

	// don't move until we are passed the muzzle flash
	if (m_AnimatedSprite.GetCurrentFrame() == 0)
		return;

	//grab the frame timer
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	//create a forward vector
	sf::Vector2f movement(1.0f, 0.0f);

	//modify magnitude based on velocity
	movement *= (m_Velocity * pFrameTimer->DeltaTime());

	//rotate and scale it to face the correct direction
	sf::Transform transform;
	transform.rotate(m_AnimatedSprite.getRotation());
	transform.scale(m_AnimatedSprite.getScale());
	movement = transform.transformPoint(movement);

	//transform the bullet position
	m_AnimatedSprite.move(movement);

	m_Lifetime -= pFrameTimer->DeltaTime();

	if (m_Lifetime <= 0.0f)
	{
		GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
		GameState* pGameState = pGameStateManager->GetCurrentGameState();
		//remove from to the current game state
		if (pGameState)
			pGameState->RemoveGameObject(this);
	}

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Bullet::GetPosition(int& x, int& y)
{
	x = (int)m_AnimatedSprite.getPosition().x;
	y = (int)m_AnimatedSprite.getPosition().y;
}

void Bullet::OnCollision(Collider2D* pCollider2D)
{
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	int colliderType2 = pCollider2D->GetCollisionType();

	if (colliderType2 != E_Collider_Bullet_Enemy && colliderType2 != E_Collider_Bullet_Player)
	{
		if ((colliderType2 != E_Collider_Enemy || m_CollisionType != E_Collider_Bullet_Enemy) && (colliderType2 != E_Collider_Player || m_CollisionType != E_Collider_Bullet_Player))
			pCurrentGameState->RemoveGameObject(this);
	}
}

void Bullet::OnCollision(TileMap* pCollider2D)
{
	//collision with a tile map object
	GameStateManager* pGameStateManager = C_SysContext::Get<GameStateManager>();
	GameState* pCurrentGameState = pGameStateManager->GetCurrentGameState();

	pCurrentGameState->RemoveGameObject(this);
}

void Bullet::SetPosition(int x, int y)
{
	m_AnimatedSprite.setPosition((float)x, (float)y);
}

void Bullet::SetRotation(float angle)
{
	m_AnimatedSprite.setRotation(angle);
}

void Bullet::SetScale(float scaleX, float scaleY)
{
	m_AnimatedSprite.setScale(scaleX, scaleY);
}

int Bullet::GetBulletDamage()
{
	return m_damageModifier;
}
