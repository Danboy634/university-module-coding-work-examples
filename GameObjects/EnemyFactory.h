#ifndef _ENEMY_FACTORY_H
#define _ENEMY_FACTORY_H

#include "EnemyBase.h"

class EnemyFactory
{
public:
	EnemyFactory();
	virtual ~EnemyFactory() = 0;

	virtual EnemyBase* MakeEnemy(int type) = 0;

private:


};

#endif