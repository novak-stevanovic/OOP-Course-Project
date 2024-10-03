#ifndef MENU_OPTION_DOSNT_EXIST_EXCEPTIONH
#define MENU_OPTION_DOSNT_EXIST_EXCEPTIONH

#include "../GenericException.h"

class MenuOptionDoesntExistException : public GenericException {

public:
    MenuOptionDoesntExistException(string msg="Menu option doesn't exist.") : GenericException(msg) {}
};

#endif

