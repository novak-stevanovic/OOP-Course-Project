#include "inventory.h"

void Inventory::addItem(Item* item, ItemStockInformationObject* infoObject) {
    _inventoryItems.addItem(item, infoObject);
}

Inventory::~Inventory() {
    for(Item* item : _inventoryItems.getKeys()) {
        delete _inventoryItems.getItemForKey(item);
        delete item;
    }
}

void Inventory::removeItem(Item* item) {
    _inventoryItems.removeItem(item);
    free(item);
}

bool Inventory::hasInStock(Item* item) const {
    return _inventoryItems.doesItemExist(item);
}

bool Inventory::hasInStock(Item* item, double amount) const {
    return (hasInStock(item) && getStockCount(item) >= amount);
}

double Inventory::getStockCount(Item* item) const {
    return _inventoryItems.getItemForKey(item)->getAmount();
}

void Inventory::setStockCount(Item* item, double amount) {
    _inventoryItems.getItemForKey(item)->setAmount(amount);
}

void Inventory::changeStockCount(Item* item, double amount) {
    setStockCount(item, getStockCount(item) + amount);
}

double Inventory::getPrice(Item* item) const {
    return _inventoryItems.getItemForKey(item)->getPricePerUnit();
}

void Inventory::setPrice(Item* item, double price) {
    _inventoryItems.getItemForKey(item)->setPricePerUnit(price);
}

void Inventory::changePrice(Item* item, double priceChange) {
    setPrice(item, getPrice(item) + priceChange);
}

ItemStockInformationObject& Inventory::getInformation(Item* item) const {
    return *_inventoryItems.getItemForKey(item);
}

const vector<Item*> Inventory::getKeys() const {
    return _inventoryItems.getKeys();
}

 ostream& operator<<(ostream& os, const Inventory& inventory) {

     for(Item* item : inventory._inventoryItems.getKeys())
         os << *item << " : " << inventory._inventoryItems.getItemForKey(item) << "\n";

     return os;

 }
