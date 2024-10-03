#ifndef USER_DATABASE_H
#define USER_DATABASE_H

#include "user.h"
#include "utility/database/database.h"

class UserDatabase : public Database<string, User*> {

public:
    virtual ~UserDatabase();
    void registerUser(User*);
};

#endif
