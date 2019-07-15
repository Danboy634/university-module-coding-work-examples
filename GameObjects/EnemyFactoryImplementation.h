#ifndef _ENEMY_FACTORY_IMPLEMENTATION_H
#define _ENEMY_FACTORY__IMPLEMENTATION_H

#include "EnemyFactory.h"

enum ENEMIES
{
	E_ENEMY_ASS,
	E_ENEMY_BOSS,
	E_ENEMY_DUCK_1,
	E_ENEMY_DUCK_2,
	E_ENEMY_DUCK_3,
	E_ENEMY_TURTLE_1,
	E_ENEMY_TURTLE_2,
	E_ENEMY_TURTLE_3,
	E_ENEMY_TURTLE_WORM,
	E_ENEMY_TURTLE_ZOMBIE
};

class EnemyFactoryImplementation
	: public EnemyFactory
{
public:
	EnemyFactoryImplementation();
	virtual ~EnemyFactoryImplementation();

	EnemyBase* MakeEnemy(int type);

private:

};

#endif