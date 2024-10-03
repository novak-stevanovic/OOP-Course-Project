#include "show_user_menu.h"
#include "show_items_start_menu.h"
#include "../utility/string/string_library.h"

ShowUserMenu::ShowUserMenu(User& user, Session& session) : Menu("Show User", session), _user(user) {}

void ShowUserMenu::initializeMenuOptions() {
    class ShowUserInformationOption : public MenuOption {

        private:
            User& _user;

        public:
            ShowUserInformationOption(User& user, Menu& parentMenu, Session& session) : MenuOption("Show User Information", parentMenu, session), _user(user) {}

            void select() override {

                cout << "* Personal information:" << endl;
                cout << StringLibrary::getIndentedString(_user.getUserInformation().toString(), 4) << endl;
                cout << "* Market Information" << endl;
                cout << StringLibrary::getIndentedString(_user.getMarketInformation().toString(), 4) << endl;
                _parentMenu.displayMenu();

            }
    };

    class ShowUserItemsOption : public MenuOption {

        private:
            User& _user;
        public:
            ShowUserItemsOption(User& user, Menu& parentMenu, Session& session) : MenuOption("Show Inventory", parentMenu, session), _user(user) {}

            void select() override {

                vector<User*> users;
                users.push_back(&_user);
                ShowItemsStartMenu showItemsMenu(users, _session);
                showItemsMenu.initializeMenuOptions();
                showItemsMenu.displayMenu();
                if(showItemsMenu.getGoBackFlag())
                    _parentMenu.displayMenu();

            }
    };

    class GoBackOption : public MenuOption {
        
        public:
            GoBackOption(Menu& parentMenu, Session& session) : MenuOption("Go Back", parentMenu, session) {}

        void select() override {
            _parentMenu.setGoBackFlag(true);
        }

    };

    ShowUserInformationOption* option1 = new ShowUserInformationOption(_user, *this, _session);
    ShowUserItemsOption* option2 = new ShowUserItemsOption(_user, *this, _session);
    GoBackOption* option3 = new GoBackOption(*this, _session);

    _menuOptions.push_back(option1);
    _menuOptions.push_back(option2);
    _menuOptions.push_back(option3);
}

void ShowUserMenu::displayMenuFooter() const {
    cout << "* " << _user.getUserInformation().getFirstName() << "'s profile" << endl;
}
