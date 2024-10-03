#ifndef ITEM_TYPE_H
#define ITEM_TYPE_H

#include "../category/category.h"
#include <iostream>

using namespace std;

class ItemType {

private:
    string _ID;
    string _stringRepresentation;
    vector<Category*> _categories;

public:

    ItemType(string, string, vector<Category*>);

    const string getID() const;
    const string getStringRepresentation() const;
    const vector<Category*> getCategories() const;

    bool operator==(const ItemType&) const;
    friend ostream& operator<<(ostream&, const ItemType&);

    virtual string toString() const;


};

#endif
