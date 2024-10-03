#include "category_selection_menu.h"
#include "../utility/category/category_printer.h"
#include "../utility/string/string_library.h"
#include "../utility/general_utility.h"

CategorySelectionMenu::CategorySelectionMenu(Session& session, const Category& rootCategory)
    : Menu("Category Selection Menu", session), _rootCategory(rootCategory), _categoryPrinter(_session.getCategoryDatabase()),
    _categoryValidator(_session.getCategoryDatabase(), _session.getSelectedCategories(), rootCategory) {}

CategorySelectionMenu::CategorySelectionMenu(Session& session) 
    : CategorySelectionMenu(session, CategoryDatabase::getRootCategory()) {}

bool CategorySelectionMenu::validateCategorySelection(Category& category) const {
    return true;
}

void CategorySelectionMenu::initializeMenuOptions() {
    class ViewFiltersOption : public MenuOption {

        private:
            const Category& _rootCategory;
            const CategoryPrinter& _printer;


        public:
            ViewFiltersOption(Menu& parentMenu, Session& session, const Category& rootCategory, const CategoryPrinter& printer) 
                : MenuOption("View Filters", parentMenu, session), _rootCategory(rootCategory), _printer(printer) {}

            void select() override {

                _printer.printCategories(_rootCategory, _session.getSelectedCategories());

                _parentMenu.displayMenu();

            }
    };

    class AddOrRemoveFilterOption : public MenuOption {
        private:
            CategoryValidator& _categoryValidator;

        public:
            AddOrRemoveFilterOption(Menu& parentMenu, Session& session, CategoryValidator& categoryValidator) 
                : MenuOption("Add or Remove Filter", parentMenu, session), _categoryValidator(categoryValidator) {}

            void select() override {

                string selectedCategoryString = inputString("Enter Category ID:");

                Category* selectedCategory = nullptr;
                try {
                    selectedCategory = _session.getCategoryDatabase().getItemForKey(selectedCategoryString);
                }
                catch (const ItemDoesntExistException& e) {
                    printFeedback(e.what());
                    _parentMenu.displayMenu();
                    return;
                }

                if(_categoryValidator.canCategoryBeSelected(*selectedCategory)) {
                    if(GeneralUtility::doesVectorContain(_session.getSelectedCategories(), selectedCategory)) {
                        GeneralUtility::eraseVectorElement(_session.getSelectedCategories(), selectedCategory);
                        printFeedback("FILTER SUCCESSFULLY REMOVED");
                    }
                    else {
                        _session.getSelectedCategories().push_back(selectedCategory);
                        printFeedback("FILTER SUCCESSFULLY ADDED");
                    }
                }
                else {
                        printFeedback("FILTER CANNOT BE SELECTED");
                }

                _parentMenu.displayMenu();

            }
    };

    class GoBackMenuOption : public MenuOption {
        public:
            GoBackMenuOption(Menu& parentMenu, Session& session) : MenuOption("Finish", parentMenu, session) {}

            void select() override {
                _parentMenu.setGoBackFlag(true);
            }
    };

    AddOrRemoveFilterOption* option1 = new AddOrRemoveFilterOption(*this, _session, _categoryValidator);
    ViewFiltersOption* option2 = new ViewFiltersOption(*this, _session, _rootCategory, _categoryPrinter);
    GoBackMenuOption* option3 = new GoBackMenuOption(*this, _session);

    _menuOptions.push_back(option1);
    _menuOptions.push_back(option2);
    _menuOptions.push_back(option3);
}


void CategorySelectionMenu::displayMenuFooter() const {
    vector<Category*>& currentlySelectedCategories = _session.getSelectedCategories();

    if(currentlySelectedCategories.size() > 0) {
        cout << "* Currently Selected Filters: " << CategoryPrinter::getCategoriesStringBrief(_session.getSelectedCategories(), ", ") << ".";
    }
    else
        cout << " * No Currently Selected Filters";

    cout << endl;
}
