#ifndef _DYNAMIC_MENU_H
#define _DYNAMIC_MENU_H

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../GameData/GameDataManager.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"
#include "../../Game/Weapons/WeaponBase.h"
#include "../../Game/Weapons/BlitzWeapon.h"
#include "../../Engine/Core/MathHelpers.h"

class DynamicMenu : public GameObject
{

public:
	DynamicMenu();
	virtual ~DynamicMenu();

	virtual void Initialise();
	virtual void Initialise(int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, int fps, bool loop);
	virtual void Update();

	virtual void GetPosition(int& x, int& y) { x = (int)m_AnimatedSprite.getPosition().x; y = (int)m_AnimatedSprite.getPosition().y; }
	bool isMoving;

	int m_Health;

private:
	AnimatedSprite m_AnimatedSprite;

};

#endif