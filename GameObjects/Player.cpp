#include "Player.h"
#include "../Weapons/BlitzWeapon.h"
#include "../Weapons/PistolWeapon.h"
#include "../Weapons/FlamethrowerWeapon.h"
#include "../Weapons/SniperWeapon.h"
#include "../Weapons/ShotgunWeapon.h"
#include "../Weapons/BossWeapon.h"
#include "../Weapons/RocketLauncherWeapon.h"
#include "../Weapons/RifleWeapon.h"
#include "../../Game/GameData/GameDataManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Engine/Core/MathHelpers.h"
#include "../../Engine/Audio/AudioManager.h"

#include "TileMap.h"
#include "Bullet.h"


Player::Player()
{
	//Collision type is used to tell what type of object has collided with another object
	m_CollisionType = E_Collider_Player;

	playerDead = false;
	gameOver = false;

	m_PrevPositionX = 0;
	m_PrevPositionY = 0;
}

Player::~Player()
{
	for (std::vector<WeaponBase*>::iterator it = m_pWeaponList.begin(); it != m_pWeaponList.end(); it++)
	{
		SAFE_DELETE_PTR(*it);
	}
	SAFE_DELETE_PTR(m_pWeapon);
}

void Player::Initialise()
{
}

void Player::Initialise(int fps, int posX, int posY)
{
	//Create an initialise all weapons that the player holds

	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();

	WeaponBase* weaponPistol = new PistolWeapon;
	m_pWeaponList.push_back(weaponPistol);
	WeaponBase* weaponBlitz = new BlitzWeapon;
	m_pWeaponList.push_back(weaponBlitz);
	WeaponBase* weaponRifle = new RifleWeapon;
	m_pWeaponList.push_back(weaponRifle);
	WeaponBase* weaponShotgun = new ShotgunWeapon;
	m_pWeaponList.push_back(weaponShotgun);
	WeaponBase* weaponSniper = new SniperWeapon;
	m_pWeaponList.push_back(weaponSniper);
	WeaponBase* weaponRocketLauncher = new RocketLauncherWeapon;
	m_pWeaponList.push_back(weaponRocketLauncher);

	for (std::vector<WeaponBase*>::iterator it = m_pWeaponList.begin(); it != m_pWeaponList.end(); it++)
	{
		(*it)->Initialise();
	}

	//set current weapon to pistol
	m_pWeapon = m_pWeaponList[E_Weapon_Pistol];
	m_CurrentWeapon = E_Weapon_Pistol;

	m_PlayerScore = 0;
	m_PlayerHealth = 6000;

	m_AnimatedSprite.setPosition((float)posX, (float)posY);
	
	GameDataManager* pGameDataManager = C_SysContext::Get <GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/spr_raff.xml");

	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Idle, pSpritesheetDef, "spr_raff_idle", fps, true);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Walk, pSpritesheetDef, "spr_raff_walk", fps);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Sprint, pSpritesheetDef, "spr_raff_sprint", fps);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Death, pSpritesheetDef, "spr_raff_death", fps, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Dig, pSpritesheetDef, "spr_raff_dig", fps, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Hit, pSpritesheetDef, "spr_raff_hit", fps, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Holo, pSpritesheetDef, "spr_raff_holo", fps, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Melee, pSpritesheetDef, "spr_raff_melee", fps, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_Dash, pSpritesheetDef, "spr_raff_dash", fps, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_teleportIn, pSpritesheetDef, "spr_raff_teleport_in", fps, false);
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(E_AnimationState_teleportOut, pSpritesheetDef, "spr_raff_teleport_out", fps, false);
	m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_teleportIn);

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();


}

void Player::Update()
{
	m_AnimatedSprite.Animate();

	if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_teleportIn)
	{
		if (m_AnimatedSprite.AnimationFinished())
		{
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
		return;
	}

	if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Death && m_AnimatedSprite.AnimationFinished())
	{
		KillPlayer();
	}
	if (m_AnimatedSprite.GetCurrentAnimation() == E_AnimationState_Hit && m_AnimatedSprite.AnimationFinished())
	{
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
	}

	int posX = 0;
	int posY = 0;
	this->GetPosition(posX, posY);
	this->m_PrevPositionX = posX;
	this->m_PrevPositionY = posY;
	
	AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();

	m_pWeapon->Update();
	this->UpdateWeapon();

	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	//check if player is moving and set the direction variable to say which direction they are moving in
	bool isMoving = (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown() || pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown() ||
		pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown() || pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown());

	if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() < 0.f)
	{
		m_AnimatedSprite.setScale(-1.f, 1.f);
	}
	else if (pInputDevice && pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue() > 0.f)
	{
		m_AnimatedSprite.setScale(1.f, 1.f);
	}

	int moveSpeedX = 0;
	int moveSpeedY = 0;

	//handles player movement
	switch (m_AnimatedSprite.GetCurrentAnimation())
	{
	case E_AnimationState_Idle:
		moveSpeedX = 0;
		moveSpeedY = 0;		

		if (isMoving)
		{
			if (pInputDevice->GetButtonInput(E_DigitalInput_LeftThumb).IsDown())
			{
				m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Sprint);
			}
			else
			{
				m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
			}
		}
		break;

	case E_AnimationState_Hit:
		if (isMoving)
		{
			if (pInputDevice->GetButtonInput(E_DigitalInput_LeftThumb).IsDown())
			{
				if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
				{
					moveSpeedX = 9;
				}
				else if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
				{
					moveSpeedX = -9;
				}
				if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
				{
					moveSpeedY = -9;
				}
				else if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
				{
					moveSpeedY = 9;
				}
			}
			else
			{
				if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
				{
					moveSpeedX = 6;
				}
				else if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
				{
					moveSpeedX = -6;
				}
				if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
				{
					moveSpeedY = -6;
				}
				else if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
				{
					moveSpeedY = 6;
				}
			}
		}
		break;

	case E_AnimationState_Walk:
		if (isMoving)
		{

			if (pInputDevice->GetButtonInput(E_DigitalInput_LeftThumb).IsDown())
			{
				m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Sprint);
			}
			if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
			{
				moveSpeedX = 6;
			}
			else if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
			{
				moveSpeedX = -6;
			}
			if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
			{
				moveSpeedY = -6;
			}
			else if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
			{
				moveSpeedY = 6;
			}
		}
		else
		{
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
		break;

	case E_AnimationState_Sprint:
		if (isMoving)
		{
			if (pInputDevice->GetButtonInput(E_DigitalInput_LeftThumb).IsDown())
			{
				if (pInputDevice->GetButtonInput(E_DigitalInput_DpadRight).IsDown())
				{
					moveSpeedX = 9;
				}
				else if (pInputDevice->GetButtonInput(E_DigitalInput_DpadLeft).IsDown())
				{
					moveSpeedX = -9;
				}
				if (pInputDevice->GetButtonInput(E_DigitalInput_DpadUp).IsDown())
				{
					moveSpeedY = -9;
				}
				else if (pInputDevice->GetButtonInput(E_DigitalInput_DpadDown).IsDown())
				{
					moveSpeedY = 9;
				}
			}
			else
			{
				m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Walk);
			}
		}
		else
		{
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Idle);
		}
		break;
	}

	m_AnimatedSprite.move((float)moveSpeedX, (float)moveSpeedY);

	//fire weapon when the appropriate input is registered
	if (pInputDevice->GetAnalogueInput(E_AnalogueInput_RightTrigger).GetValue() > 0)
	{
		this->Fire();
	}

	//reload weapon
	if (pInputDevice->GetButtonInput(E_DigitalInput_X).IsDown() || m_pWeapon->GetWeaponAmmo() == 0 && m_pWeapon->GetAmmoInBag() > 0)
	{
		this->Reload();
		/*pAudioManager->PlaySoundFX("sounds/sfx_reload_loop2.wav");
		pAudioManager->Update();*/
	}

	//switch between all weapons
	//controller
	if (pInputDevice->GetButtonInput(E_DigitalInput_Y).OnPressed())
	{
		m_pWeapon->SetPosition(-10000000, -10000000);
		m_pWeaponList[m_CurrentWeapon] = m_pWeapon;
		if (m_CurrentWeapon == (E_Weapon_Max - 1))
		{
			m_CurrentWeapon = 0;
			m_pWeapon = m_pWeaponList[m_CurrentWeapon];
		}
		else
		{
			m_pWeapon = m_pWeaponList[m_CurrentWeapon + 1];
			m_CurrentWeapon++;
		}
	}

	//keyboard
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && m_CurrentWeapon != E_Weapon_Pistol && m_pWeapon)
	{

		pAudioManager->PlaySoundFX("sounds/sfx_detector_far.wav");
		m_pWeapon->SetPosition(-10000000, -10000000);
		m_pWeaponList[m_CurrentWeapon] = m_pWeapon;
		m_pWeapon = m_pWeaponList[E_Weapon_Pistol];
		m_CurrentWeapon = E_Weapon_Pistol;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && m_CurrentWeapon != E_Weapon_Blitz && m_pWeapon)
	{
		pAudioManager->PlaySoundFX("sounds/sfx_detector_far.wav");
		m_pWeapon->SetPosition(-10000000, -10000000);
		m_pWeaponList[m_CurrentWeapon] = m_pWeapon;
		m_pWeapon = m_pWeaponList[E_Weapon_Blitz];
		m_CurrentWeapon = E_Weapon_Blitz;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && m_CurrentWeapon != E_Weapon_Rifle && m_pWeapon)
	{
		pAudioManager->PlaySoundFX("sounds/sfx_detector_far.wav");
		m_pWeapon->SetPosition(-10000000, -10000000);
		m_pWeaponList[m_CurrentWeapon] = m_pWeapon;
		m_pWeapon = m_pWeaponList[E_Weapon_Rifle];
		m_CurrentWeapon = E_Weapon_Rifle;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && m_CurrentWeapon != E_Weapon_Shotgun && m_pWeapon)
	{
		pAudioManager->PlaySoundFX("sounds/sfx_detector_far.wav");
		m_pWeapon->SetPosition(-10000000, -10000000);
		m_pWeaponList[m_CurrentWeapon] = m_pWeapon;
		m_pWeapon = m_pWeaponList[E_Weapon_Shotgun];
		m_CurrentWeapon = E_Weapon_Shotgun;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && m_CurrentWeapon != E_Weapon_Sniper && m_pWeapon)
	{
		pAudioManager->PlaySoundFX("sounds/sfx_detector_far.wav");
		m_pWeapon->SetPosition(-10000000, -10000000);
		m_pWeaponList[m_CurrentWeapon] = m_pWeapon;
		m_pWeapon = m_pWeaponList[E_Weapon_Sniper];
		m_CurrentWeapon = E_Weapon_Sniper;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && m_CurrentWeapon != E_Weapon_RocketLauncher && m_pWeapon)
	{
		pAudioManager->PlaySoundFX("sounds/sfx_detector_far.wav");
		m_pWeapon->SetPosition(-10000000, -10000000);
		m_pWeaponList[m_CurrentWeapon] = m_pWeapon;
		m_pWeapon = m_pWeaponList[E_Weapon_RocketLauncher];
		m_CurrentWeapon = E_Weapon_RocketLauncher;
	}

	m_CollisionRect = m_AnimatedSprite.getGlobalBounds();
}

void Player::UpdateWeapon()
{
	InputManager* pInputManager = C_SysContext::Get<InputManager>();
	InputDevice* pInputDevice = pInputManager->GetInputDevice();

	float angle = 0.0f;

	if (pInputDevice)
	{
		float thumbXPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRX).GetValue();
		float thumbYPos = pInputDevice->GetAnalogueInput(E_AnalogueInput_ThumbRY).GetValue();

		//up vector and positions of the right thumbstick to get two vectors to calculate the angle the weapon needs to be pointing
		sf::Vector2f up(0.0f, -1.0f);
		sf::Vector2f forwards(thumbXPos, thumbYPos);

		angle = (MathHelpers::AngleBetweenVectors(up, forwards)) - 90.f;
	}

	//angle negative if the sprite is facing the other direction
	angle = m_AnimatedSprite.getScale().x < 0.0f ? -angle : angle;

	float weaponOffsetX = 0.f;
	float weaponOffsetY = 0.f;
	m_pWeapon->GetWeaponOffset(weaponOffsetX, weaponOffsetY);

	m_pWeapon->SetPosition(m_AnimatedSprite.getPosition().x + weaponOffsetX * m_AnimatedSprite.getScale().x,
		m_AnimatedSprite.getPosition().y + weaponOffsetY * m_AnimatedSprite.getScale().y);
	m_pWeapon->SetRotation(angle);
	m_pWeapon->SetScale(m_AnimatedSprite.getScale().x, m_AnimatedSprite.getScale().y);

	m_pWeapon->Update();
}

void Player::GetPosition(int& x, int& y)
{
	x = (int)m_AnimatedSprite.getPosition().x;
	y = (int)m_AnimatedSprite.getPosition().y;
}

void Player::GetCollidePosition(int& x, int& y)
{
	x = (int)m_AnimatedSprite.getPosition().x;
	y = (int)m_AnimatedSprite.getPosition().y + (int)(m_CollisionRect.height / 2) - 15;
}

void Player::Fire()
{
	if (m_pWeapon)
	{
		m_pWeapon->Fire(E_Collider_Bullet_Player);
	}
}

void Player::Reload()
{
	if (m_pWeapon)
	{
		m_reloading = true; 

		m_pWeapon->Reload();
	}
}

bool Player::getReloadState()
{
	return m_reloading;
}

void Player::hasReloaded()
{
	isReloaded = m_pWeapon->isReloaded(); //sets isReloaded boolean to WB class reloaded value

	if (isReloaded) //If the gun has reloaded
	{
		m_reloading = false; //Stop reloading
	}
}

int Player::getWeaponAmmo()
{
	return m_pWeapon->GetWeaponAmmo();
}

int Player::getAmmoInBag()
{
	return m_pWeapon->GetAmmoInBag();
}

void Player::setAmmoInBag(int ammoValue)
{
	m_pWeapon->SetAmmoInBag(10);
}

int Player::getClipMax()
{
	return m_pWeapon->GetClipMax();
}

int Player::getCurrentWeapon()
{
	return m_CurrentWeapon;
}

int Player::getCurrentScore()
{
	return m_PlayerScore;
}

void Player::AddPointsToScore(int points)
{
	m_PlayerScore += points;
}

void Player::LosePointsFromScore(int points)
{
	m_PlayerScore -= points;
}

int Player::getCurrentHealth()
{
	return m_PlayerHealth;
}

void Player::GainHealth(int value)
{
	m_PlayerHealth += value;
}

void Player::LoseHealth(int value)
{
	m_PlayerHealth -= value;

	if (this->IsPlayerDead() && !playerDead)
	{
		playerDead = true;
		m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Death);
	}
}

void Player::OnCollision(Collider2D* pCollider2D)
{
	Bullet* bullet = (Bullet*)pCollider2D;

	//if player collides with enemy bullet then player loses health
	if (pCollider2D->GetCollisionType() == E_Collider_Bullet_Enemy)
	{
		if (m_AnimatedSprite.GetCurrentAnimation() != E_AnimationState_Death)
			m_AnimatedSprite.SetCurrentAnimation(E_AnimationState_Hit);

		this->LoseHealth(bullet->GetBulletDamage());
	}
}

void Player::OnCollision(TileMap* pCollider2D)
{ 
	//collision with a tile map object
	m_AnimatedSprite.setPosition((float)m_PrevPositionX, (float)m_PrevPositionY);
}

bool Player::IsPlayerDead()
{
	if (m_PlayerHealth <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::KillPlayer()
{
	gameOver = true;
}

bool Player::GameOver()
{
	return gameOver;
}
