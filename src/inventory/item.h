#ifndef ITEM_H
#define ITEM_H

#include "category/category_database.h"
#include "item_type/item_type.h"
#include "category/category.h"
#include "string"

using namespace std;

class Item {

private:
    ItemType& _itemType;
    vector<Category*> _categories;

public:

    Item(ItemType&, vector<Category*>);

    ItemType& getItemType() const;
    bool matchesCriteria(const vector<Category*>&) const;
    bool operator==(const Item&) const;
    const vector<Category*>& getCategories() const;
    friend ostream& operator<<(ostream&, const Item&);
    virtual string toString() const;

};

#endif
