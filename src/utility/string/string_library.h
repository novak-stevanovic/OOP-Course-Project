#ifndef STRING_LIBRARY_H
#define STRING_LIBRARY_H

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "../database/database.h"

using namespace std;

class StringLibrary {
public:
    static vector<string> splitByDelimiter(string, char);
    static bool isParsableToInt(string);
    static string getIndentedString(string, int);
};

#endif
