#ifndef CATEGORY_VALIDATOR_H
#define CATEGORY_VALIDATOR_H

#include "category_database.h"
class CategoryValidator {

private:
    const CategoryDatabase& _categoryDatabase;
    vector<Category*>& _selectedCategories;
    const Category& _rootCategory;
public:
    CategoryValidator(const CategoryDatabase&, vector<Category*>&, const Category&);

    bool canCategoryBeSelected(const Category&) const;


};

#endif
