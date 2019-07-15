#ifndef  _ITEM_FACTORY_H
#define _ITEM_FACTORY_H

#include "Item.h"

class ItemFactory
{
public:
	ItemFactory();
	virtual ~ItemFactory() = 0;

	virtual Item* MakeItem(int type) = 0;
};

#endif // ! _ITEM_FACTORY_H
