#ifndef START_MENU_H
#define START_MENU_H

#include "menu.h"
#include "../session/session.h"

class StartMenu : public Menu {

private:
    void displayMenuFooter() const override;

public:
    StartMenu(Session&);
    void initializeMenuOptions() override;

};

#endif
