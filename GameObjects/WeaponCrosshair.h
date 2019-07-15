#ifndef _WEAPON_CROSSHAIR_H
#define _WEAPON_CROSSHAIR_H

#include "../../Engine/Core/GameObject.h"
#include "../../Engine/Renderer/Sprite.h"

class WeaponCrosshair 
	: public GameObject
{
public:
	WeaponCrosshair();
	virtual ~WeaponCrosshair();

	virtual void Initialise();
	virtual void Initialise(char* filename);
	virtual void Update();
	virtual void GetPosition(int& x, int& y);

private:
	Sprite m_Sprite;

};

#endif