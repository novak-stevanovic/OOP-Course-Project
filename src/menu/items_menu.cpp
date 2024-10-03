#include "items_menu.h"
#include "category_selection_menu.h"
#include "item_menu.h"
#include "../inventory/category/category_database.h"

ItemsMenu::ItemsMenu(vector<User*>& users, Session& session) : Menu("Items Menu", session), _userPool(users) {}

void ItemsMenu::initializeMenuOptions() {

    removeMenuOptions();

    class GoBackOption : public MenuOption {
        public:
            GoBackOption(Menu& parentMenu, Session& session) : MenuOption("Go Back", parentMenu, session) {}

            void select() override {
                _parentMenu.setGoBackFlag(true);
            }
    };

    class ItemOption : public MenuOption {
        private:
            User& _user;
            Item& _item;
            ItemStockInformationObject& _info;

        public:
            ItemOption(User& user, Item& item, Menu& parentMenu, ItemStockInformationObject& info, Session& session) 
                : MenuOption(item.getItemType().getStringRepresentation() + " | " + user.getUserInformation().getUsername(), parentMenu, session), _user(user), _item(item), _info(info) {}

            void select() override {
                ItemMenu itemMenu(_user, _item, _info, _session);
                itemMenu.initializeMenuOptions();
                itemMenu.displayMenu();
                if(itemMenu.getGoBackFlag()) {
                    _parentMenu.initializeMenuOptions();
                    _parentMenu.displayMenu();
                }
            }

    };

    class ViewAllItemTypesOption : public MenuOption {
        public:
            ViewAllItemTypesOption(Menu& parentMenu, Session& session) 
                : MenuOption("View All Item Types ", parentMenu, session) {}

            void select() override {
                int i = 1;
                for(ItemType* it : _session.getItemTypeDatabase().getValues())
                    cout << i++ << ") NAME: " << *it << " | ID: " << it->getID() << " | CATEGORIES: " << CategoryPrinter::getCategoriesStringBrief(it->getCategories(), ", ") << "." << endl;

                _parentMenu.initializeMenuOptions();
                _parentMenu.displayMenu();
            }
    };

    class AddItemOption : public MenuOption {

        public:
            AddItemOption(Menu& parentMenu, Session& session) 
                : MenuOption("Add Item", parentMenu, session) {}

            void select() override {
                _session.clearSelectedCategories();
                string itemTypeID = inputString("Enter Item Type ID:");

                ItemType* it;
                try {
                    it = _session.getItemTypeDatabase().getItemForKey(itemTypeID);
                }
                catch (const ItemDoesntExistException& e) {
                    printFeedback(e.what());
                    _parentMenu.displayMenu();
                    return;
                }

                double pricePerUnit = inputDouble("Enter Price Per Unit:");
                int amount = inputDouble("Enter Amount:");

                ItemStockInformationObject* infoObject = new ItemStockInformationObject(pricePerUnit, amount);

                CategorySelectionMenu categorySelection(_session, CategoryDatabase::getItemRootCategory());
                categorySelection.initializeMenuOptions();
                categorySelection.displayMenu();

                Item* newItem = new Item(*it, _session.getSelectedCategories());
                
                try {
                    _session.getCurrentUser()->getInventory().addItem(newItem, infoObject);
                }
                catch (ItemAlreadyExistsException& e) {
                    cout << e.what() << endl;
                    return;
                }

                printFeedback("ITEM SUCCESSFULLY ADDED");
                printFeedback("FILTERS CLEARED");
                _session.clearSelectedCategories();

                _parentMenu.initializeMenuOptions();
                _parentMenu.displayMenu();
            }

    };

    for(User* u : _userPool) {
        for(Item* i : u->getInventory().getKeys()) {
            if(i->matchesCriteria(_session.getSelectedCategories())) {
                _menuOptions.push_back(new ItemOption(*u, *i, *this, u->getInventory().getInformation(i), _session));
            }
        }

    }

    if((_userPool.size() == 1) && (_userPool.at(0)->getUserInformation().getUsername() == _session.getCurrentUser()->getUserInformation().getUsername())) {
        _menuOptions.push_back(new AddItemOption(*this, _session));
        _menuOptions.push_back(new ViewAllItemTypesOption(*this, _session));
    }

    _menuOptions.push_back(new GoBackOption(*this, _session));

}

void ItemsMenu::displayMenuFooter() const {
    if(_userPool.size() == 1) 
        cout << "* " << _userPool.at(0)->getUserInformation().getUsername() << "'s Items";
    else 
        cout << "* All Items";

    cout << " - ";
    if(_session.getSelectedCategories().empty())
        cout << "No Filters Selected.";
    else
        cout << CategoryPrinter::getCategoriesStringBrief(_session.getSelectedCategories(), ", ") << ".";

    cout << endl;
}
