#ifndef LOGGED_IN_MENU
#define LOGGED_IN_MENU

#include "menu.h"
#include "../session/session.h"

class LoggedInMenu : public Menu {

private:
    void displayMenuFooter() const override;

public:
    LoggedInMenu(Session&);
    void initializeMenuOptions() override;

};

#endif
