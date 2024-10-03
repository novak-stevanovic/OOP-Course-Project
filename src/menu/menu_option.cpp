#include "menu_option.h"

MenuOption::MenuOption(string text, Menu& parentMenu, Session& session) : _text(text), _parentMenu(parentMenu), _session(session) {}

string MenuOption::getText() const {
    return _text;
}

MenuOption::~MenuOption() {}
