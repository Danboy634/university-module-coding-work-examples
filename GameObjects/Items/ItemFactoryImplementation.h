#ifndef  ITEM_FACTORY_IMPLEMENTATION_H
#define  ITEM_FACTORY_IMPLEMENTATION_H

#include "ItemFactory.h"
#include "ammoPickup.h"
#include "healthPickup.h"

enum itemTypes
{
	E_ammoPickup,
	E_healthPickup
};

class ItemFactoryImplementation :
	public ItemFactory
{
public:
	ItemFactoryImplementation();
	~ItemFactoryImplementation();

	Item* MakeItem(int type);


};

#endif // ! ITEM_FACTORY_IMPLEMENTATION_H
