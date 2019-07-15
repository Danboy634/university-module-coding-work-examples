#ifndef _GAME_OBJECT_WITH_ANIMATED_SPRITE_H
#define _GAME_OBJECT_WITH_ANIMATED_SPRITE_H

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/AnimatedSprite.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Input/InputDevice.h"

class GameObjectWithAnimatedSprite :
	public GameObject
{
public:
	GameObjectWithAnimatedSprite();
	~GameObjectWithAnimatedSprite();

	virtual void Initialise();
	void Initialise(const int spriteID, const char* spriteSheetFileName, const char* animationName, const int fps, bool loop, int posX, int posY);
	virtual void Update();
	void Update(int scaleX);
	virtual void GetPosition(int& x, int& y); //Two integer reference parameters; x and y

	bool AnimationFinished();

private:
	AnimatedSprite m_AnimatedSprite;
};

#endif