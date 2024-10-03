#include "category_database.h"


Category* CategoryDatabase::ROOT_CATEGORY = new Category("super_category", "All Categories", nullptr, false);
Category* CategoryDatabase::ITEM_TYPE_ROOT_CATEGORY = new Category("item_type_categories", "Item Type Categories", ROOT_CATEGORY, false);
Category* CategoryDatabase::ITEM_ROOT_CATEGORY = new Category("item_categories", "Item Categories", ROOT_CATEGORY, false);

CategoryDatabase::CategoryDatabase() {
    addItem(ROOT_CATEGORY->getID(), ROOT_CATEGORY);
    addItem(ITEM_TYPE_ROOT_CATEGORY->getID(), ITEM_TYPE_ROOT_CATEGORY);
    addItem(ITEM_ROOT_CATEGORY->getID(), ITEM_ROOT_CATEGORY);
}

CategoryDatabase::~CategoryDatabase() {
    for(string s : getKeys()) {
        delete getItemForKey(s);
    }
}

const Category& CategoryDatabase::getRootCategory() {
    return *ROOT_CATEGORY;
}
const Category& CategoryDatabase::getItemTypeRootCategory() {
    return *ITEM_TYPE_ROOT_CATEGORY;
}
const Category& CategoryDatabase::getItemRootCategory() {
    return *ITEM_ROOT_CATEGORY;
}
