#ifndef ITEM_DOESNT_EXIST_EXCEPTION_H
#define ITEM_DOESNT_EXIST_EXCEPTION_H

#include "../../GenericException.h"

class ItemDoesntExistException : public GenericException {

public:
    ItemDoesntExistException(string msg="Item doesn't exist.") : GenericException(msg) {}
};

#endif
