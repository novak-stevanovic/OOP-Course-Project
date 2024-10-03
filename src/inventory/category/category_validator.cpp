#include "category_validator.h"

CategoryValidator::CategoryValidator(const CategoryDatabase& categoryDatabase, vector<Category*>& selectedCategories, const Category& rootCategory) 
    : _categoryDatabase(categoryDatabase), _selectedCategories(selectedCategories), _rootCategory(rootCategory) {}


bool CategoryValidator::canCategoryBeSelected(const Category& category) const {
    return category.isDescendedFrom(_rootCategory);
}
