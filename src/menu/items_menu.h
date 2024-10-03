#ifndef ITEMS_MENU_H
#define ITEMS_MENU_H

#include "menu.h"
#include "../user.h"

class ItemsMenu : public Menu {

private:
    vector<User*>& _userPool;
    void displayMenuFooter() const override;

public:
    ItemsMenu(vector<User*>&, Session&);
    void initializeMenuOptions() override;

};


#endif
