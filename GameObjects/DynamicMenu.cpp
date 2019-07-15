#include "DynamicMenu.h"
#include "../../Engine/Utils/Utils.h"

DynamicMenu::DynamicMenu()
{

}

DynamicMenu::~DynamicMenu()
{

}

void DynamicMenu::Initialise()
{

	// Loads in sprite animation
	GameDataManager* pGameDataManager = C_SysContext::Get<GameDataManager>();
	SpritesheetDef* pSpritesheetDef = pGameDataManager->GetSpritesheetDef("sprites/characters/menu_dynamic.xml");
	
	// set fps to 10
	int fps = 10;

	// add the animation from xml
	m_AnimatedSprite.AddAnimationFromSpriteSheetDef(0, pSpritesheetDef, "spr_logo", fps, false);
	
	// set the position
	m_AnimatedSprite.setPosition(700, 100);

	// set the current animation
	m_AnimatedSprite.SetCurrentAnimation(0);
}

void DynamicMenu::Initialise(int animationId, SpritesheetDef* pSpritesheetDef, const char* animationName, int fps, bool loop)
{
}

void DynamicMenu::Update()
{
	FrameTimer* pFrameTimer = C_SysContext::Get<FrameTimer>();

	InputManager* pInputManager = C_SysContext::Get<InputManager>(); 
	InputDevice* pInputDevice = pInputManager->GetInputDevice(); 

	// animate the sprite
	m_AnimatedSprite.Animate();
}