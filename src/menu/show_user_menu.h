#ifndef SHOW_USER_MENU_H
#define SHOW_USER_MENU_H

#include "menu.h"
#include "../user.h"

class ShowUserMenu : public Menu {

private:
    User& _user;
    void displayMenuFooter() const override;

public:
    ShowUserMenu(User&, Session&);
    void initializeMenuOptions() override;

};

#endif

