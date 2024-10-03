#ifndef SESSION_H
#define SESSION_H

#include "../user_database.h"
#include "../inventory/category/category_database.h"
#include "../inventory/item_type/item_type_database.h"

class Session {
private:
    int _ID;
    static int _IDGenerator;
    UserDatabase& _userDatabase;
    ItemTypeDatabase& _itemTypeDatabase;
    CategoryDatabase& _categoryDatabase;
    vector<Category*> _selectedCategories;
    User* _currentUser;

public:
    Session(UserDatabase&, ItemTypeDatabase&, CategoryDatabase&);

    void loginUser(string, string);
    void logoutUser();

    int getID() const;
    User* getCurrentUser() const;
    bool isLoggedIn() const;

    void clearSelectedCategories();

    const CategoryDatabase& getCategoryDatabase() const;
    UserDatabase& getUserDatabase() const;
    const ItemTypeDatabase& getItemTypeDatabase() const;
    vector<Category*>& getSelectedCategories();
};

#endif
