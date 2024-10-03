#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include "item_stock_information_object.h"
#include <unordered_map>
#include "../utility/database/database.h"

using namespace std;

class Inventory {

private:
    Database<Item*, ItemStockInformationObject*> _inventoryItems;

public:
    ~Inventory();
    void addItem(Item*, ItemStockInformationObject*);
    void removeItem(Item*);

    bool hasInStock(Item*) const;
    bool hasInStock(Item*, double) const;
    ItemStockInformationObject& getInformation(Item*) const;

    double getStockCount(Item*) const;
    void changeStockCount(Item*, double);
    void setStockCount(Item*, double);

    double getPrice(Item*) const;
    void changePrice(Item*, double);
    void setPrice(Item*, double);

    const vector<Item*> getKeys() const;

    friend ostream& operator<<(ostream&, const Inventory&);

};

#endif
