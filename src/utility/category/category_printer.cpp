#include "category_printer.h"
#include "../general_utility.h"

CategoryPrinter::CategoryPrinter(const CategoryDatabase& categoryDatabase, char selectedDirectly, char selectedIndirectly, char notSelected, char unselectable) 
    : _categories(categoryDatabase), _selectedDirectly(selectedDirectly), _selectedIndirectly(selectedIndirectly), _notSelected(notSelected), _unselectable(unselectable) {}

CategoryPrinter::CategoryPrinter(const CategoryDatabase& categoryDatabase) : CategoryPrinter(categoryDatabase, '+', '>', '-', '*') {}

bool shouldSelectCategoryIndirectly(const Category& category, const vector<Category*>& selectedCategories) {
    for(Category* c : selectedCategories) {
        if((*c == category) || category.isDescendedFrom(*c)) {
            return true;
        }
    }
    return false;
}

void CategoryPrinter::printCategory(const Category& category, const vector<Category*>& selectedCategories, int indent) const {

    for (int i = 0; i < indent; i++)
        cout << " ";

    char prefix;
    if(!category.isSelectable())
        cout << _unselectable << " " << category.getName() << endl;
    else {
        if(GeneralUtility::doesVectorContain(selectedCategories, category))
            prefix = _selectedDirectly;
        else if(shouldSelectCategoryIndirectly(category, selectedCategories)) 
            prefix = _selectedIndirectly;
        else
            prefix = _notSelected;

        cout << prefix << " " << category << " | " << category.getID() << endl;
    }

    for(Category* c : category.getPossibleSubcategories()) {
        printCategory(*c, selectedCategories, indent+2);
    }

}

void CategoryPrinter::printCategories(const Category& rootCategory, const vector<Category*>& selectedCategories) const {
    printCategory(rootCategory, selectedCategories, 0);
}

void CategoryPrinter::printCategories(const vector<Category*>& selectedCategories) const {
    printCategories(CategoryDatabase::getRootCategory(), selectedCategories);
}

string CategoryPrinter::getCategoriesStringBrief(const vector<Category*>& categories, string delimiter) {
    if(categories.size() == 0) return "";

    string outputString = "";
    int i;
    for (i = 0; i < categories.size() - 1; i++)
        outputString += categories.at(i)->getName() + delimiter;
    outputString += categories.at(i)->getName();

    return outputString;

}

string CategoryPrinter::getCategoriesStringDetailed(const vector<Category*>& categories, string delimiter, string fieldDelimiter) {
    if(categories.size() == 0) return "";

    string outputString = "";
    int i;
    for (i = 0; i < categories.size() - 1; i++)
        outputString += categories.at(i)->getName() + fieldDelimiter + categories.at(i)->getID() + delimiter;
    outputString += categories.at(i)->getName() + fieldDelimiter + categories.at(i)->getID();

    return outputString;


}
