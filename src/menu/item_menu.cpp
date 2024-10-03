#include "item_menu.h"
#include "../utility/string/string_library.h"
#include "../utility/category/category_printer.h"


ItemMenu::ItemMenu(User& user, Item& item, ItemStockInformationObject& info, Session& session) 
    : Menu("Item Menu", session), _user(user), _item(item), _info(info) {}

void ItemMenu::initializeMenuOptions() {
    
    class GoBackOption : public MenuOption {
        public:
            GoBackOption(Menu& parentMenu, Session& session) : MenuOption("Go Back", parentMenu, session) {}

            void select() override {
                _parentMenu.setGoBackFlag(true);
            }
    };

    class MoreInfoOption : public MenuOption {
        private:
            Item& _item;
            ItemStockInformationObject& _info;
        public:
            MoreInfoOption(Menu& parentMenu, Item& item, ItemStockInformationObject& info, Session& session) 
                : MenuOption("More Information", parentMenu, session), _item(item), _info(info) {}

            void select() override {
                cout << "* Item Type:" << endl;
                cout << StringLibrary::getIndentedString("ID: " + _item.getItemType().getID(), 4) << endl;
                cout << StringLibrary::getIndentedString("Name: " + _item.getItemType().getStringRepresentation(), 4) << endl;
                cout << StringLibrary::getIndentedString("Categories: ", 4) << endl;
                string itemTypeCategoriesString = CategoryPrinter::getCategoriesStringDetailed(_item.getItemType().getCategories(), "\n", " | ");
                cout << StringLibrary::getIndentedString(itemTypeCategoriesString, 6) << endl;

                if(_item.getCategories().empty())
                    cout << "* No Categories." << endl;
                else {
                    cout << "* Categories:" << endl;
                    string itemCategoriesString = CategoryPrinter::getCategoriesStringDetailed(_item.getCategories(), "\n", " | ");
                    cout << StringLibrary::getIndentedString(itemCategoriesString, 4) << endl;
                }

                cout << "* PRICE PER UNIT: " << _info.getPricePerUnit() << " | " << "AMOUNT: " << _info.getAmount() << endl;

                _parentMenu.displayMenu();
            }
    };

    class BuyItemOption : public MenuOption {
        private:
            Item& _item;
            User& _buyer;
            User& _seller;

        public:
            BuyItemOption(Menu& parentMenu, User& buyer, User& seller, Item& item, Session& session) 
                : MenuOption("Buy Item", parentMenu, session), _item(item), _buyer(buyer), _seller(seller) {}

            void select() override {
                printFeedback("Seller: "+ _seller.getUserInformation().getUsername());
                int amount = inputDouble("Enter Amount:");
                try {
                    if(_buyer.canBuyItem(_seller, &_item, amount)) {
                        _buyer.buyItem(_seller, &_item, amount);
                        printFeedback("ITEM SUCCESSFULLY BOUGHT");
                    }
                    else {
                        printFeedback("CAN'T BUY THAT ITEM");
                    }
                }
                catch (ItemDoesntExistException& e) {
                    printFeedback(e.what());
                }

                _parentMenu.displayMenu();
            }
    };

    class RemoveItemOption : public MenuOption {
        private:
            Item& _item;
            User& _user;

        public:
            RemoveItemOption(Menu& parentMenu, User& user, Item& item, Session& session) 
                : MenuOption("Remove Item", parentMenu, session), _item(item), _user(user) {}

            void select() override {
                try {
                    _user.getInventory().removeItem(&_item);
                    printFeedback("ITEM SUCCESSFULLY REMOVED");
                }
                catch (const ItemDoesntExistException& e) {
                    printFeedback(e.what());
                }

                _parentMenu.setGoBackFlag(true);

            }
    };
    
    class ChangeStockCountOption : public MenuOption {
        private:
            Item& _item;
            User& _user;

        public:
            ChangeStockCountOption(Menu& parentMenu, User& user, Item& item, Session& session) 
                : MenuOption("Change Stock Count", parentMenu, session), _item(item), _user(user) {}

            void select() override {
                double amount = inputDouble("Enter Amount:");
                try {
                    _user.getInventory().changeStockCount(&_item, amount);
                    printFeedback("COUNT SUCCESSFULLY CHANGED");
                }
                catch (const ItemDoesntExistException& e) {
                    printFeedback(e.what());
                }
                _parentMenu.displayMenu();
            }
    };

    class SetStockPriceOption : public MenuOption {
        private:
            Item& _item;
            User& _user;

        public:
            SetStockPriceOption(Menu& parentMenu, User& user, Item& item, Session& session) 
                : MenuOption("Change Stock Price", parentMenu, session), _item(item), _user(user) {}

            void select() override {
                double amount = inputDouble("Enter Amount:");
                try {
                    _user.getInventory().setPrice(&_item, amount);
                    printFeedback("PRICE SUCCESSFULLY SET");
                }
                catch (const ItemDoesntExistException& e) {
                    printFeedback(e.what());
                }

                _parentMenu.displayMenu();
            }
    };

    MoreInfoOption* moreInfoOption = new MoreInfoOption(*this, _item, _info, _session);
    GoBackOption* goBackOption = new GoBackOption(*this, _session);

    _menuOptions.push_back(moreInfoOption);

    if(!(_session.getCurrentUser()->getUserInformation().getUsername() == _user.getUserInformation().getUsername())) {
        BuyItemOption* buyItemOption = new BuyItemOption(*this, *_session.getCurrentUser(), _user, _item, _session);
        _menuOptions.push_back(buyItemOption);
    }
    else {
        _menuOptions.push_back(new ChangeStockCountOption(*this, *_session.getCurrentUser(), _item, _session));
        _menuOptions.push_back(new SetStockPriceOption(*this, *_session.getCurrentUser(), _item, _session));
        _menuOptions.push_back(new RemoveItemOption(*this, *_session.getCurrentUser(), _item, _session));
    }

    _menuOptions.push_back(goBackOption);

}
void ItemMenu::displayMenuFooter() const {

    cout << "* Current Item: " << _item << endl;

}
