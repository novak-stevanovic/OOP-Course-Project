#ifndef LOADER_H
#define LOADER_H

#include "database.h"
template <typename T1, typename T2>
class Loader {

public:
    virtual Database<T1, T2>* loadDatabase() = 0;

};

#endif
