#ifndef ITEM_ALREADY_EXISTS_EXCEPTION_H
#define ITEM_ALREADY_EXISTS_EXCEPTION_H

#include "../../GenericException.h"

class ItemAlreadyExistsException : public GenericException {

public:
    ItemAlreadyExistsException(string msg="Entry already exists.") : GenericException(msg) {}
};

#endif

