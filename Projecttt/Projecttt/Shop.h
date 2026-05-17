#ifndef SHOP_H
#define SHOP_H

#include"Item.h"

class Shop{
private:
	Item* items;
	int itemsInInventory;
public:
	Shop();
	~Shop();
	void addItem(Item& newItem);
	//void removeItem(Item& item);
};

#endif