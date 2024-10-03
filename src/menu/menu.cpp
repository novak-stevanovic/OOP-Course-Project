#include "menu.h"
#include <iostream>
#include "../utility/string/string_library.h"

Menu::Menu(string name, Session& session) : _name(name),  _goBackFlag(false), _session(session) {}

Menu::~Menu() {
    for(MenuOption* option : _menuOptions) {
        delete option;
    }
}

void Menu::displayMenu() {
    printDelimiter();
    int i = 1;
    cout << _name << endl << endl;
    for(MenuOption* option : _menuOptions) {
        cout << i << ") " << option->getText() << endl;
        i++;
    }

    cout << endl;
    displayMenuFooter();
    printDelimiter();

    string input;
    do {
        input = inputString("Enter option:");
    } while((!StringLibrary::isParsableToInt(input)) || (stoi(input) - 1) >= _menuOptions.size());

    selectOption(stoi(input) - 1);
}

void Menu::displayMenuFooter() const {}

void Menu::selectOption(int index) {
    if((_menuOptions.size() <= index) || (index < 0))
        printFeedback("Invalid menu option. Try Again. ");

    _menuOptions.at(index)->select();
}


string Menu::inputString(string text) {
    string returnValue;
    cout << "[...] " << text << " ";
    cin >> returnValue;
    return returnValue;
}

int Menu::inputInt(string text) {
    int returnValue;
    cout << "[...] " << text << " ";
    cin >> returnValue;
    return returnValue;
}

double Menu::inputDouble(string text) {
    double returnValue;
    cout << "[...] " << text << " ";
    cin >> returnValue;
    return returnValue;
}

void Menu::removeMenuOptions() {
    for (auto it = _menuOptions.begin(); it != _menuOptions.end(); ) {
        delete *it;  // Delete the object pointed to by the iterator
        it = _menuOptions.erase(it);  // Erase the element and get the next valid iterator
    }}

string Menu::getName() const {
    return _name;
}

const vector<MenuOption*>& Menu::getMenuOptions() {
    return _menuOptions;
}

bool Menu::getGoBackFlag() const {
    return _goBackFlag;
}

void Menu::setGoBackFlag(bool value) {
    _goBackFlag = value;

}

void Menu::printFeedback(string s) {
    cout << "[!] " << s << endl;
}

void Menu::printDelimiter() {
    cout << "----------------------------------------------------------------------------" << endl;
}
