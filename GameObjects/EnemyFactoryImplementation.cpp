#include "EnemyFactoryImplementation.h"
#include "../GameObjects/EnemyAss.h"
#include "../GameObjects/EnemyBoss.h"
#include "../GameObjects/EnemyDuck1.h"
#include "../GameObjects/EnemyDuck2.h"
#include "../GameObjects/EnemyDuck3.h"
#include "../GameObjects/EnemyTurtle1.h"
#include "../GameObjects/EnemyTurtle2.h"
#include "../GameObjects/EnemyTurtle3.h"
#include "../GameObjects/EnemyTurtleWorm.h"
#include "../GameObjects/EnemyTurtleZombie.h"

EnemyFactoryImplementation::EnemyFactoryImplementation()
{
}

EnemyFactoryImplementation::~EnemyFactoryImplementation()
{
}

EnemyBase * EnemyFactoryImplementation::MakeEnemy(int type)
{
	EnemyBase* enemy = nullptr;

	switch (type)
	{
	case E_ENEMY_ASS:
		enemy = new EnemyAss();

		break;

	case E_ENEMY_BOSS:
		enemy = new EnemyBoss();

		break;

	case E_ENEMY_DUCK_1:
		enemy = new EnemyDuck1();

		break;

	case E_ENEMY_DUCK_2:
		enemy = new EnemyDuck2();

		break;

	case E_ENEMY_DUCK_3:
		enemy = new EnemyDuck3();

		break;

	case E_ENEMY_TURTLE_1:
		enemy = new EnemyTurtle1();

		break;

	case E_ENEMY_TURTLE_2:
		enemy = new EnemyTurtle2();

		break;

	case E_ENEMY_TURTLE_3:
		enemy = new EnemyTurtle3();

		break;

	case E_ENEMY_TURTLE_WORM:
		enemy = new EnemyTurtleWorm();

		break;

	case E_ENEMY_TURTLE_ZOMBIE:
		enemy = new EnemyTurtleZombie();

		break;
	}

	return enemy;
}
