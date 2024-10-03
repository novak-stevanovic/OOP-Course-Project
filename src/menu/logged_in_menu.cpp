#include "logged_in_menu.h"
#include "show_items_start_menu.h"
#include "show_user_menu.h"

LoggedInMenu:: LoggedInMenu(Session& session) : Menu("Start Menu", session) {}

void LoggedInMenu::initializeMenuOptions() {

    class LogoutMenuOption : public MenuOption {
        public:
            LogoutMenuOption(Session& session, Menu& parentMenu) : MenuOption("Log Out", parentMenu, session) {}

            void select() override {

                _session.logoutUser();
                printFeedback("SUCESSFULLY LOGGED OUT.");
                _parentMenu.setGoBackFlag(true);

            }
    };
    class ViewAllItemsOption : public MenuOption {
        public:
            ViewAllItemsOption(Session& session, Menu& parentMenu) : MenuOption("View Market", parentMenu, session) {}

            void select() override {

                vector<User*> users = _session.getUserDatabase().getValues();
                ShowItemsStartMenu sm(users, _session);
                sm.initializeMenuOptions();
                sm.displayMenu();
                if(sm.getGoBackFlag())
                    _parentMenu.displayMenu();

            }
    };

    class ViewOwnProfileOption : public MenuOption {
        public:
            ViewOwnProfileOption(Session& session, Menu& parentMenu) : MenuOption("View Own Profile", parentMenu, session) {}

            void select() override {

                ShowUserMenu showUserMenu(*_session.getCurrentUser(), _session);
                showUserMenu.initializeMenuOptions();
                showUserMenu.displayMenu();
                if(showUserMenu.getGoBackFlag())
                    _parentMenu.displayMenu();

            }
    };

    class ViewOtherProfileOption : public MenuOption {
        public:
            ViewOtherProfileOption(Session& session, Menu& parentMenu) : MenuOption("View Other Profile", parentMenu, session) {}

            void select() override {
                string enteredUsername = inputString("Enter Username:");

                User* u = nullptr;
                try {
                    u = _session.getUserDatabase().getItemForKey(enteredUsername);
                }
                catch (const ItemDoesntExistException& e) {
                    printFeedback(e.what());
                    _parentMenu.displayMenu();
                    return;
                }
                ShowUserMenu showUserMenu(*u, _session);
                showUserMenu.initializeMenuOptions();
                showUserMenu.displayMenu();
                if(showUserMenu.getGoBackFlag())
                    _parentMenu.displayMenu();


            }
    };

    class ViewAllProfilesOption : public MenuOption {
        public:
            ViewAllProfilesOption(Session& session, Menu& parentMenu) : MenuOption("Show All Users", parentMenu, session) {}

            void select() override {

                for(User* user : _session.getUserDatabase().getValues()) {
                    cout << *user << " | ID: " << user->getUserInformation().getUsername() << endl;
                }
                _parentMenu.displayMenu();
            }
    };
    class DepositMoneyOption : public MenuOption {
        public:
            const int depositMoneyAmount = 100;
            DepositMoneyOption(Session& session, Menu& parentMenu) : MenuOption("Deposit Money", parentMenu, session) {}

            void select() override {

                _session.getCurrentUser()->getMarketInformation().setBalance(_session.getCurrentUser()->getMarketInformation().getBalance() + depositMoneyAmount);
                printFeedback("Added " + to_string(depositMoneyAmount) + "$");
                _parentMenu.displayMenu();
            }
    };

    ViewOwnProfileOption* option1 = new ViewOwnProfileOption(_session, *this);
    ViewAllProfilesOption* option2 = new ViewAllProfilesOption(_session, *this);
    ViewOtherProfileOption* option3 = new ViewOtherProfileOption(_session, *this);
    ViewAllItemsOption* option4 = new ViewAllItemsOption(_session, *this);
    DepositMoneyOption* option5 = new DepositMoneyOption(_session, *this);
    LogoutMenuOption* option6 = new LogoutMenuOption(_session, *this);

    _menuOptions.push_back(option1);
    _menuOptions.push_back(option2);
    _menuOptions.push_back(option3);
    _menuOptions.push_back(option4);
    _menuOptions.push_back(option5);
    _menuOptions.push_back(option6);
}


void LoggedInMenu::displayMenuFooter() const {
    cout << "* Currently logged in as: " << _session.getCurrentUser()->getUserInformation().getUsername() << endl;
}
