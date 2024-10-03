#ifndef ITEM_TYPE_DATABASE_H
#define ITEM_TYPE_DATABASE_H

#include "item_type.h"
#include "../../utility/database/database.h"

class ItemTypeDatabase : public Database<string, ItemType*> {

public:
    virtual ~ItemTypeDatabase();
};

#endif

