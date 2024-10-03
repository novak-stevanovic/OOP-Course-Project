#ifndef CATEGORY_LOADER_H
#define CATEGORY_LOADER_H

#include "../category_database.h"
#include "../../../utility/database/loader.h"

class CategoryLoader : Loader<string, Category*> {

public:
    virtual CategoryDatabase* loadDatabase() = 0;
};


#endif
