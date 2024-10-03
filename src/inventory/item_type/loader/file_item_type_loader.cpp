#include "file_item_type_loader.h"
#include "../../../utility/string/string_library.h"

FileItemTypeLoader::FileItemTypeLoader(CategoryDatabase& categoryDatabase, ifstream& fileStream) 
    : ItemTypeLoader(categoryDatabase), _fileStream(fileStream) {}


ItemType* FileItemTypeLoader::getItemTypeForTokens(const vector<string>& tokens) {
    string currentItemID = tokens.at(0);

    vector<Category*> categories;

    string stringRepresentation = tokens.at(1);

    for (int i = 2; i < tokens.size(); i++) {
        categories.push_back(_categoryDatabase.getItemForKey(tokens.at(i)));
    }
    
    ItemType* item = new ItemType(currentItemID, stringRepresentation, categories);

    return item;
    
}

ItemTypeDatabase* FileItemTypeLoader::loadDatabase() {

    ItemTypeDatabase* database = new ItemTypeDatabase();
    string line;
    while (getline(_fileStream, line)) {
        vector<string> tokens = StringLibrary::splitByDelimiter(line, ',');
        ItemType* itemType = getItemTypeForTokens(tokens);
        database->addItem(itemType->getID(), itemType);
    }

    return database;

}
