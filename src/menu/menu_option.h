#ifndef MENU_OPTION_H
#define MENU_OPTION_H

#include <string>
#include "../session/session.h"

using namespace std;

class Menu;

class MenuOption {

protected:
    string _text;
    Menu& _parentMenu;
    Session& _session;

public:
    MenuOption(string, Menu&, Session&);
    virtual ~MenuOption();
    string getText() const;
    virtual void select() = 0;

};

#endif
