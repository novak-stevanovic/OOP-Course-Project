#ifndef CATEGORY_DATABASE_H
#define CATEGORY_DATABASE_H

#include "category.h"
#include <string>
#include "../../utility/database/database.h"

using namespace std;

class CategoryDatabase : public Database<string, Category*> {

private:
    static Category* ROOT_CATEGORY;
    static Category* ITEM_TYPE_ROOT_CATEGORY;
    static Category* ITEM_ROOT_CATEGORY;
public:
    CategoryDatabase();
    virtual ~CategoryDatabase();
    static const Category* a;

    static const Category& getRootCategory();
    static const Category& getItemTypeRootCategory();
    static const Category& getItemRootCategory();
    static bool doesAncestorExist(const Category&, const vector<Category*>&);
};

#endif
