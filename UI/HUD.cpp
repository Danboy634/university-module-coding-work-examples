#include "HUD.h"
#include <string>

HUD::HUD()
{
	isReloading = false;
}

HUD::~HUD()
{
	C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(&m_WeaponSprite);
	C_SysContext::Get<RenderManager>()->RemoveUIRenderObject(&m_ReloadSprite);
}

void HUD::Initialise()
{

}

void HUD::Initialise(int fps, const char* font)
{
	GameDataManager* ptrGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* ptrSpritesheetDef = ptrGameDataManager->GetSpritesheetDef("sprites/weapons/UI_Weapons.xml");
	
	C_SysContext::Get<RenderManager>()->RemoveRenderObject(&m_WeaponSprite);

	m_WeaponSprite.AddAnimationFromSpriteSheetDef(E_Weapon_Pistol, ptrSpritesheetDef, "UI_spr_pistol_plasma", fps, true);
	m_WeaponSprite.AddAnimationFromSpriteSheetDef(E_Weapon_Blitz, ptrSpritesheetDef, "UI_spr_blitz", fps, true);
	m_WeaponSprite.AddAnimationFromSpriteSheetDef(E_Weapon_Rifle, ptrSpritesheetDef, "UI_spr_ducan_rifle", fps, true);
	m_WeaponSprite.AddAnimationFromSpriteSheetDef(E_Weapon_Shotgun, ptrSpritesheetDef, "UI_spr_shotgun_heavy", fps, true);
	m_WeaponSprite.AddAnimationFromSpriteSheetDef(E_Weapon_Sniper, ptrSpritesheetDef, "UI_spr_ducan_sniper", fps, true);
	m_WeaponSprite.AddAnimationFromSpriteSheetDef(E_Weapon_RocketLauncher, ptrSpritesheetDef, "UI_spr_ducan_rocket_launcher", fps, true);
	m_WeaponSprite.setScale(2, 2);
	m_WeaponSprite.SetCurrentAnimation(E_Weapon_Pistol);

	C_SysContext::Get<RenderManager>()->AddUIRenderObject(&m_WeaponSprite);

	GameDataManager* ptr_Reload_GameDataManager = C_SysContext::Get <GameDataManager>();
	SpritesheetDef* ptr_Reload_SpritesheetDef = ptr_Reload_GameDataManager->GetSpritesheetDef("sprites/ui/Reloading.xml");

	m_ReloadSprite.AddAnimationFromSpriteSheetDef(0, ptr_Reload_SpritesheetDef, "spr_reload_char", 10, true);
	m_ReloadSprite.SetCurrentAnimation(0);

	m_Score.Initialise(font, "Score: ");
	m_Health.Initialise(font, "Health: ");
	m_Ammo.Initialise(font, "Ammo: ");
	m_Reload.Initialise(font, "Reload!");
	m_Score.SetVisible(true);
	m_Health.SetVisible(true);


	if (isReloading)
	{
		AudioManager* pAudioManager = C_SysContext::Get<AudioManager>();
		pAudioManager->PlaySoundFX("sounds/sfx_reload.wav");
	}

}

void HUD::Update()
{
}

void HUD::Update(int ammoValue, int totalAmmo, int clipValue, int scoreValue, int healthValue)
{
	
	PlayerPtr->hasReloaded();
	m_weaponSpriteIndex = PlayerPtr->getCurrentWeapon();

	m_WeaponSprite.SetCurrentAnimation(m_weaponSpriteIndex);
	m_WeaponSprite.Pause();

	isReloading = PlayerPtr->getReloadState();

	if (isReloading)
	{
		m_Ammo.SetVisible(false);
		m_Reload.SetVisible(true);

		m_ReloadSprite.SetVisible(true); 
		m_ReloadSprite.Animate();
	}
	else if (!isReloading)
	{
		m_Reload.SetVisible(false);
		m_Ammo.SetVisible(true);
		m_ReloadSprite.SetVisible(false);
	}

	std::string str = std::to_string(ammoValue) + "/" + std::to_string(totalAmmo);
	m_Ammo.Update(str.c_str());

	std::string str2 = std::to_string(scoreValue);
	m_Score.Update(str2.c_str());

	std::string str3 = std::to_string(healthValue);
	m_Health.Update(str3.c_str());

}

void HUD::GetPosition(int& x, int& y)
{
	x = 0;
	y = 0;
}

void HUD::SetPosition(int AmmoX, int AmmoY, int WepX, int WepY, int ScoreX, int ScoreY, int HealthX, int HealthY)
{	
	m_WeaponSprite.setPosition((float)WepX - 60, (float)WepY + 20);

	m_Ammo.GetText().setPosition((float)(AmmoX - 200), (float)(AmmoY + 30));
	m_Ammo.GetText2().setPosition((float)(AmmoX - 10), (float)(AmmoY + 31));

	m_Reload.GetText().setPosition((float)(AmmoX - 300), (float)(AmmoY + 30));

	m_Score.GetText().setPosition((float)(ScoreX - 240), (float)(ScoreY));
	m_Score.GetText2().setPosition((float)(ScoreX - 30), (float)(ScoreY + 1));

	m_Health.GetText().setPosition((float)(HealthX - 130), (float)(HealthY));
	m_Health.GetText2().setPosition((float)(HealthX + 90), (float)(HealthY + 1));
}

void HUD::setReloadSpritePosition(int playerPositionX, int playerPositionY)
{
	m_ReloadSprite.setPosition((float)playerPositionX, (float)playerPositionY + 50.f);
}