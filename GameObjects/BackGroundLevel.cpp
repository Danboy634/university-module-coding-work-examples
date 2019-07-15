#include "GameObjectWithSprite.h"
#include "BackgroundLevel.h"
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/System/GameState/GameStateManager.h"
#include "../../Engine/System/GameState/GameState.h"

BackgroundLevel::BackgroundLevel()
{
}

BackgroundLevel::~BackgroundLevel()
{
}

void BackgroundLevel::Initialise()
{
}

void BackgroundLevel::InitialiseLevelOne(const char* filename, const int xPos, const int yPos, const int sizeX, const int sizeY)
{
	// initialises the first level with filename, position and scale
	m_Sprite.Initialise(filename, xPos, yPos, sizeX, sizeY);
	m_Sprite.setPosition(-500, -500);
	m_Sprite.setScale(1500, 1500);

}

void BackgroundLevel::InitialiseLevelTwo(const char *filename, const int xPos, const int yPos, const int sizeX, const int sizeY)
{

	// initialises the second level with filename, position and scale
	Background_Box_Image.Initialise(filename, xPos, yPos, sizeX, sizeY);
	Background_Box_Image.setPosition(-500, -500);
	Background_Box_Image.setScale(1500, 1500);
}

void BackgroundLevel::Update()
{

}

void BackgroundLevel::GetPosition(int& x, int& y)
{
	x = (int)m_Sprite.getPosition().x;
	y = (int)m_Sprite.getPosition().y;
}

