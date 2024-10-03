#include "show_items_start_menu.h"
#include "category_selection_menu.h"
#include "items_menu.h"

ShowItemsStartMenu::ShowItemsStartMenu(vector<User*>& userPool, Session& session) : Menu("Show Items General Menu", session), _userPool(userPool) {}

void ShowItemsStartMenu::initializeMenuOptions() {

    class StartCategorySelectionMenu : public MenuOption {

        public:
            StartCategorySelectionMenu(Menu& parentMenu, Session& session) : MenuOption("Filter Menu", parentMenu, session) {}

            void select() override {

                CategorySelectionMenu selectionMenu(_session);
                selectionMenu.initializeMenuOptions();
                selectionMenu.displayMenu();
                if(selectionMenu.getGoBackFlag())
                    _parentMenu.displayMenu();

            }
    };

    class StartItemsMenuOption : public MenuOption {

        private:
            vector<User*>& _users;

        public:
            StartItemsMenuOption(vector<User*>& users, Menu& parentMenu, Session& session) : MenuOption("Show Items", parentMenu, session), _users(users) {}

            void select() override {

                ItemsMenu itemsMenu(_users, _session);
                itemsMenu.initializeMenuOptions();
                itemsMenu.displayMenu();
                if(itemsMenu.getGoBackFlag())
                    _parentMenu.displayMenu();

            }
    };

    class GoBackOption : public MenuOption {
        public:
            GoBackOption(Menu& parentMenu, Session& session) : MenuOption("Go Back", parentMenu, session) {}

            void select() override {
                _session.clearSelectedCategories();
                printFeedback("FILTERS CLEARED");
                _parentMenu.setGoBackFlag(true);
            }
    };

    StartCategorySelectionMenu* categorySelectionOption = new StartCategorySelectionMenu(*this, _session);
    GoBackOption* goBackOption = new GoBackOption(*this, _session);

    _menuOptions.push_back(categorySelectionOption);
    _menuOptions.push_back(new StartItemsMenuOption(_userPool, *this, _session));
    _menuOptions.push_back(goBackOption);
}

void ShowItemsStartMenu::displayMenuFooter() const {

    if(_userPool.size() == 1) 
        cout << "* " << _userPool.at(0)->getUserInformation().getUsername() << "'s Inventory";
    else 
        cout << "* Market";

    cout << " - ";
    if(_session.getSelectedCategories().empty())
        cout << "No Filters Selected.";
    else
        cout << CategoryPrinter::getCategoriesStringBrief(_session.getSelectedCategories(), ", ") << ".";

    cout << endl;

}
