#ifndef  _CAMERA_H
#define _CAMERA_H

#include "../../Engine/Core/GameObject.h"
#include <SFML\Graphics.hpp>
#include "../../Engine/System/Context/SysContextProvider.h"
#include "../../Engine/Renderer/WindowManager.h"
#include "../../Game/GameObjects/Player.h"

class Camera :
	public GameObject
{
public:	
	Camera();
	virtual ~Camera();

	virtual void Initialise();
	virtual void Update();
	virtual void Update(int positionX, int positionY);
	virtual void GetPosition(int& x, int& y);
	void SetAsCurrentCamera();
	void RemoveCamera();

private:
	sf::View m_View;
	bool m_Active;
	//Player* playerPtr;
	//int positionX;
	//int positionY;
};
#endif // ! _CAMERA_H
