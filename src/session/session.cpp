#include "session.h"

int Session::_IDGenerator = 0;

Session::Session(UserDatabase& userDatabase, ItemTypeDatabase& itemTypeDatabase, CategoryDatabase& categoryDatabase) 
    : _ID(++_IDGenerator), _userDatabase(userDatabase), _itemTypeDatabase(itemTypeDatabase), _categoryDatabase(categoryDatabase), _currentUser(nullptr) {}

void Session::loginUser(string username, string password) {
    if(_userDatabase.doesItemExist(username) && _userDatabase.getItemForKey(username)->getUserInformation().checkPassword(password)) {
        _currentUser = _userDatabase.getItemForKey(username);
    }
}

void Session::logoutUser() {
    _currentUser = nullptr;
}

User* Session::getCurrentUser() const {
    return _currentUser;
}

bool Session::isLoggedIn() const { 
    return _currentUser != nullptr;
}

UserDatabase& Session::getUserDatabase() const {
    return _userDatabase;
}
const ItemTypeDatabase& Session::getItemTypeDatabase() const {
    return _itemTypeDatabase;
}

const CategoryDatabase& Session::getCategoryDatabase() const {
    return _categoryDatabase;
}

vector<Category*>& Session::getSelectedCategories() {
    return _selectedCategories;
}

int Session::getID() const {
    return _ID;
}

void Session::clearSelectedCategories() {
    _selectedCategories.clear();
}
