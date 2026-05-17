#include"Shop.h"


Shop::Shop() {
	items = nullptr;
	itemsInInventory = 0;
}

Shop::~Shop() {
	if (items)
		delete[] items;
}

void Shop::addItem(Item& newItem) {

	Item* temp = new Item[itemsInInventory + 1];

	for (int i = 0; i < itemsInInventory; i++) {
		temp[i] = items[i];
	}

	if (items)
		delete[] items;

	temp[itemsInInventory] = newItem;

	items = temp;

	itemsInInventory++;

}

//void Shop::removeItem(Item& removableItem) {
//
//	Item* temp = new Item[itemsInInventory - 1];
//	int j = 0;
//
//	for (int i = 0; i < itemsInInventory; i++) {
//		if (!(items[i] == removableItem)) {
//			temp[j] = items[i];
//			j++;
//		}
//	}
//
//	if (items)
//		delete[] items;
//
//	items = temp;
//
//	itemsInInventory--;
//
//}

