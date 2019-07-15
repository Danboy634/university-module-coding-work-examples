#ifndef _BACK_GROUND_LEVEL_H
#define _BACK_GROUND_LEVEL_H

#include "../../Engine/Renderer/Sprite.h"
#include "../../Engine/Core/GameObject.h"

class BackgroundLevel
	: public GameObject
{
public:
	BackgroundLevel();
	~BackgroundLevel();

	void Initialise();
	void InitialiseLevelOne(const char* filename, const int xPos, const int yPos, const int sizeX, const int sizeY);
	void InitialiseLevelTwo(const char* filename, const int xPos, const int yPos, const int sizeX, const int sizeY);
	void Update();
	void GetPosition(int& x, int& y);


private:
	Sprite m_Sprite, Background_Box_Image;
};

#endif
