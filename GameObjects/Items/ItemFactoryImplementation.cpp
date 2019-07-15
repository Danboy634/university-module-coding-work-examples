#include "ItemFactoryImplementation.h"

ItemFactoryImplementation::ItemFactoryImplementation()
{
}


ItemFactoryImplementation::~ItemFactoryImplementation()
{
}

Item * ItemFactoryImplementation::MakeItem(int type)
{
	Item* pickUp = nullptr;

	switch (type)
	{
	case E_ammoPickup:
	{
		pickUp = new ammoPickup();
	}
	break;

	case E_healthPickup:
	{
		pickUp = new healthPickup();
	}
	break;

	}
	return pickUp;
}
