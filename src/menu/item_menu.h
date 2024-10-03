#ifndef ITEM_MENU_H
#define ITEM_MENU_H

#include "menu.h"
#include "../user.h"

class ItemMenu : public Menu {

private:
    User& _user;
    Item& _item;
    ItemStockInformationObject& _info;
    virtual void displayMenuFooter() const override;

public:
    ItemMenu(User&, Item&, ItemStockInformationObject&, Session&);
    void initializeMenuOptions() override;

};

#endif
