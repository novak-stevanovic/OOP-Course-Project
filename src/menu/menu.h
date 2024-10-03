#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include "menu_option.h"

using namespace std;

class Menu {

    protected:
        string _name;
        Session& _session;
        vector<MenuOption*> _menuOptions;
        virtual void displayMenuFooter() const;
        bool _goBackFlag;
        void removeMenuOptions();
        static string inputString(string);
        static int inputInt(string);
        static double inputDouble(string);
        static void printDelimiter();

    public:
        Menu(string, Session&);
        ~Menu();

        virtual void initializeMenuOptions() = 0;
        void setGoBackFlag(bool);
        void displayMenu();
        virtual void selectOption(int);
        string getName() const;
        bool getGoBackFlag() const;
        const vector<MenuOption*>& getMenuOptions();

        static void printFeedback(string);
        static void printFeedback(string, int);
};

#endif
