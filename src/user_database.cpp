#include "user_database.h"

void UserDatabase::registerUser(User* newUser) {
    this->addItem(newUser->getUserInformation().getUsername(), newUser);
}

UserDatabase::~UserDatabase() {
    for(string s : getKeys()) {
        delete getItemForKey(s);
    }
}
