#include "category.h"
#include "../../utility/database/item_already_exists_exception.h"

Category::Category(string ID, string name, Category* superCategory, bool selectable) 
    : _ID(ID), _name(name), _superCategory(superCategory), _selectable(selectable) {

    if(_superCategory != nullptr)
        _superCategory->addPossibleSubcategory(this);
}

const string Category::getName() const {
    return _name;
}

const string Category::getID() const {
    return _ID;
}

void Category::addPossibleSubcategory(Category* _newValue) {
    if(hasSubcategory(_newValue))
        throw ItemAlreadyExistsException();

    _possibleValues.push_back(_newValue);
}

const vector<Category*>& Category::getPossibleSubcategories() const {
    return _possibleValues;
}

void getAllSubcategories(const Category* currentCategory, vector<Category*>& allSubcategories) {

    for(Category* c : currentCategory->getPossibleSubcategories()) {
        if(!c) continue;
        allSubcategories.push_back(c);
        getAllSubcategories(c, allSubcategories);
    }

}

const vector<Category*> Category::getAllSubcategories() const {
    vector<Category*> allSubcategories;
    ::getAllSubcategories(this, allSubcategories);
    return allSubcategories;
}

bool Category::hasSubcategory(string valueID) const {
    for(Category* c : _possibleValues) {
        if(c->_ID == valueID)
            return true;
    }

    return false;
}

bool Category::hasSubcategory(Category* category) const {
    return(hasSubcategory(category->_ID));
}

bool Category::operator==(const Category& category) const {
    return this->_ID == category._ID;
}

Category* Category::getSuperCategory() const {
    return _superCategory;
}

bool Category::hasSuperCategory() const {
    return _superCategory != nullptr;
}

const bool Category::isDescendedFrom(const Category& category) const {

    const Category* currentCategory = this;

    while(currentCategory->hasSuperCategory()) {
        currentCategory = currentCategory->getSuperCategory();
        if(*currentCategory == category)
            return true;
    
    }

    return false;

}

ostream& operator<<(ostream& os, const Category& category) {
    os << category.toString();
    return os;
}

bool Category::isSelectable() const {
    return _selectable;
}

string Category::toString() const {
    return getName();

}
