#ifndef ITEM_TYPE_LOADER_H
#define ITEM_TYPE_LOADER_H

#include "../item_type_database.h"
#include "../../category/category_database.h"
#include "../../../utility/database/loader.h"

class ItemTypeLoader : Loader<string, ItemType*> {

protected:
    CategoryDatabase& _categoryDatabase;
public:
    ItemTypeLoader(CategoryDatabase&);
    virtual ItemTypeDatabase* loadDatabase() = 0;
};

#endif
