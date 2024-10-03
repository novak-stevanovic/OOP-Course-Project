#ifndef FILE_TYPE_ITEM_LOADER_H
#define FILE_TYPE_ITEM_LOADER_H

#include <vector>
#include <fstream>
#include <string>

#include "item_type_loader.h"

using namespace std;

class FileItemTypeLoader : public ItemTypeLoader {

private:
    ifstream& _fileStream;
    ItemType* getItemTypeForTokens(const vector<string>&);

public:
    FileItemTypeLoader(CategoryDatabase&, ifstream&);
    virtual ItemTypeDatabase* loadDatabase() override;
};

#endif
