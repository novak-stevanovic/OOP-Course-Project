#include "item.h"

Item::Item(ItemType& itemType, vector<Category*> categories) 
    : _itemType(itemType), _categories(categories) {}

ItemType& Item::getItemType() const {
    return _itemType;
}

bool Item::operator==(const Item& other) const {
    return ((other._itemType == _itemType) && (other._categories == _categories));
}

ostream& operator<<(ostream& os, const Item& item) {
    os << item.toString();
    return os;
}

string Item::toString() const {
    return _itemType.toString();
}

//aaaaaaaaaaaaaaaa
bool Item::matchesCriteria(const vector<Category*>& criteria) const {

    list<Category*> joinedCategories;
    for(Category* c : _categories) {
        joinedCategories.push_back(c);
    }
    for(Category* c : _itemType.getCategories()) {
        joinedCategories.push_back(c);
    }
    
    bool pass = false;
    for(Category* c : criteria) {
        for(Category* c2 : joinedCategories) {
            if(c2->isDescendedFrom(*c) || c2->getID() == c->getID())
                pass = true;
        }
        if(pass == false)
            return false;
    }

    return true;
}

const vector<Category*>& Item::getCategories() const {
    return _categories;
}

