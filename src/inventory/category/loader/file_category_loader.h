#ifndef FILE_CATEGORY_LOADER_H
#define FILE_CATEGORY_LOADER_H

#include <string>
#include <fstream>

#include "category_loader.h"
#include "../category.h"

using namespace std;

class FileCategoryLoader : public CategoryLoader {

private:
    ifstream& _fileStream;
    Category* getCategoryForTokens(const vector<string>&, const CategoryDatabase&) const;

public:
    FileCategoryLoader(ifstream&);
    virtual CategoryDatabase* loadDatabase() override;

};

#endif
