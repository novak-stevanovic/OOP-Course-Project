#ifndef CATEGORY_PRINTER_H
#define CATEGORY_PRINTER_H

#include "../../inventory/category/category_database.h"

class CategoryPrinter {

private:
    char _selectedDirectly, _selectedIndirectly, _notSelected, _unselectable;

    const CategoryDatabase& _categories;
    void printCategory(const Category&, const vector<Category*>&, int) const;
public:
    CategoryPrinter(const CategoryDatabase&, char, char, char, char);
    CategoryPrinter(const CategoryDatabase&);
    void printCategories(const vector<Category*>&) const;
    void printCategories(const Category&, const vector<Category*>&) const;

    static string getCategoriesStringBrief(const vector<Category*>&, string);
    static string getCategoriesStringDetailed(const vector<Category*>&, string, string);

};

#endif
