#ifndef GENERIC_EXCEPTION_H
#define GENERIC_EXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

class GenericException : public exception
{
    protected:
        string _msg;

    public:
        GenericException(string msg) : _msg(msg) {}

        const char* what() const noexcept override {
            return _msg.c_str();
        }
};

#endif
