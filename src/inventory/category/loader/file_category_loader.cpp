#include "file_category_loader.h"
#include "../../../utility/string/string_library.h"

FileCategoryLoader::FileCategoryLoader(ifstream& fileStream) : _fileStream(fileStream) {}

Category* FileCategoryLoader::getCategoryForTokens(const vector<string>& tokens, const CategoryDatabase& database) const {
    Category* superCategory = nullptr;
    bool selectable;

    if(tokens.at(1) != "NONE")
        superCategory = database.getItemForKey(tokens.at(1));

    if(tokens.at(2) == "1")
        selectable = true;
    else
        selectable = false;

    string name = tokens.at(3);

    return new Category(tokens.at(0), name, superCategory, selectable);
}

CategoryDatabase* FileCategoryLoader::loadDatabase() {
    CategoryDatabase* database = new CategoryDatabase();

    string line;
    while(getline(_fileStream, line)) {
        vector<string> tokens = StringLibrary::splitByDelimiter(line, ',');
        Category* category = getCategoryForTokens(tokens, *database);
        try {
            database->addItem(category->getID(), category);
        } catch (const ItemAlreadyExistsException& e) {
            cout << e.what() << endl;
        }
    }

    return database;
}
