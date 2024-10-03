#ifndef CATEGORY_SELECTION_MENU_H
#define CATEGORY_SELECTION_MENU_H

#include "menu.h"
#include "../utility/category/category_printer.h"
#include "../inventory/category/category_validator.h"

class CategorySelectionMenu : public Menu {

private:
    const Category& _rootCategory;
    void displayMenuFooter() const override;
    bool validateCategorySelection(Category&) const;

    CategoryPrinter _categoryPrinter;
    CategoryValidator _categoryValidator;

public:
    CategorySelectionMenu(Session& session, const Category& rootCategory);
    CategorySelectionMenu(Session& session);
    void initializeMenuOptions() override;
    const Category* getRootCategory() const;

};

#endif
