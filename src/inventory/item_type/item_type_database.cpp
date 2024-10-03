#include "item_type_database.h"

ItemTypeDatabase::~ItemTypeDatabase() {
    for(string s : getKeys()) {
        delete getItemForKey(s);
    }
}
