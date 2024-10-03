#include "inventory/category/category_database.h"
#include "inventory/category/loader/file_category_loader.h"
#include "inventory/item_type/item_type_database.h"
#include "inventory/item_type/loader/file_item_type_loader.h"
#include "menu/start_menu.h"
#include "session/session.h"
#include <fstream>

using namespace std;

int main (int argc, char *argv[]) {

    ifstream categoryDatabaseFileStream("../resource/categories.csv");

    if(!categoryDatabaseFileStream) {
        cerr << "Error opening item type categories database file." << std::endl;
        return 1;
    }
    FileCategoryLoader categoryLoader(categoryDatabaseFileStream);
    CategoryDatabase* categoryDatabase = categoryLoader.loadDatabase();
    categoryDatabaseFileStream.close();

    ifstream itemTypeFilestream("../resource/item_types.csv");
    if(!itemTypeFilestream) {
        cerr << "Error opening item type items database file." << std::endl;
        return 1;
    }
    FileItemTypeLoader itemTypeLoader(*categoryDatabase, itemTypeFilestream);
    ItemTypeDatabase* itemTypeDatabase = itemTypeLoader.loadDatabase();
    itemTypeFilestream.close();



    cout << "WELCOME" << endl;

    UserDatabase* userDatabase = new UserDatabase();

    Session s(*userDatabase, *itemTypeDatabase, *categoryDatabase);
    StartMenu sm(s);
    sm.initializeMenuOptions();
    sm.displayMenu();

    delete categoryDatabase;
    delete itemTypeDatabase;
    delete userDatabase;

    return 0;
}
