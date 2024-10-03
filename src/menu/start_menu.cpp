#include "start_menu.h"
#include "logged_in_menu.h"

StartMenu::StartMenu(Session& session) : Menu("Start Menu", session) {}

void StartMenu::initializeMenuOptions() {

    class LoginMenuOption : public MenuOption {
        
        public:
            LoginMenuOption(Session& session, Menu& parentMenu) : MenuOption("Log in", parentMenu, session) {}

            void select() override {

                string enteredUsername = inputString("Enter Username:");
                string enteredPassword = inputString("Enter Password:");
                _session.loginUser(enteredUsername, enteredPassword);

                if(_session.isLoggedIn()) {
                    printFeedback("LOGIN SUCCESSFUL.");

                    LoggedInMenu m(_session);
                    m.initializeMenuOptions();
                    m.displayMenu();
                    if(m.getGoBackFlag())
                        _parentMenu.displayMenu();
                }
                else {
                    printFeedback("LOGIN FAILED.");
                    _parentMenu.displayMenu();
                    
                }


            }
    };

    class RegisterMenuOption : public MenuOption {
        
        public:
            RegisterMenuOption(Session& session, Menu& parentMenu) : MenuOption("Register", parentMenu, session) {}

            void select() override {

                string enteredUsername = inputString("Enter Username:");
                string enteredFirstName = inputString("Enter First Name:");
                string enteredLastName = inputString("Enter Last Name:");
                string enteredPassword = inputString("Enter Password:");
                string enteredPhoneNumber = inputString("Enter Phone Number:");

                User::UserInformation* userInformation = new User::UserInformation(enteredUsername, enteredFirstName, enteredLastName, enteredPassword, enteredPhoneNumber);

                User* user = new User(userInformation);

                try {
                    _session.getUserDatabase().registerUser(user);
                    printFeedback("SUCCESSFULLY REGISTERED. ");
                }
                catch (const ItemAlreadyExistsException& e) {
                    printFeedback(e.what());
                }


                _parentMenu.displayMenu();

            }
    };

    class ExitOption : public MenuOption {
        public:
            ExitOption(Menu& parentMenu, Session& session) : MenuOption("Exit", parentMenu, session) {}

            void select() override {}
    };

    LoginMenuOption* option1 = new LoginMenuOption(_session, *this);
    RegisterMenuOption* option2 = new RegisterMenuOption(_session, *this);
    ExitOption* option3 = new ExitOption(*this, _session);

    _menuOptions.push_back(option1);
    _menuOptions.push_back(option2);
    _menuOptions.push_back(option3);

}

void StartMenu::displayMenuFooter() const {
    cout << "* Not logged in." << endl;
}

