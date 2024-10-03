#include "item_type.h"

ItemType::ItemType(string ID, string stringRepresentation, vector<Category*> categories) 
    : _ID(ID), _stringRepresentation(stringRepresentation), _categories(categories) {}

const string ItemType::getStringRepresentation() const {
    return _stringRepresentation;
}

const string ItemType::getID() const {
    return _ID;
}

const vector<Category*> ItemType::getCategories() const {
    return _categories;
}

bool ItemType::operator==(const ItemType& other) const {
    return (_ID == other._ID);
}

ostream& operator<<(ostream& os, const ItemType& itemType) {

    os << itemType.toString();

    return os;
}


string ItemType::toString() const {
    return _stringRepresentation;

}
