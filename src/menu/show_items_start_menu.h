#ifndef SHOW_ITEMS_START_MENU_H
#define SHOW_ITEMS_START_MENU_H

#include "../user.h"
#include "menu.h"

class ShowItemsStartMenu : public Menu {

private:
    vector<User*>& _userPool;
    void displayMenuFooter() const override;

public:
    ShowItemsStartMenu(vector<User*>&, Session&);

    void initializeMenuOptions() override;

};

#endif

