#include "string_library.h"

vector<string> StringLibrary::splitByDelimiter(string stringToSplit, char delimiter) {
    vector<string> tokens;

    if(stringToSplit.empty())
        return tokens;

    string currentToken;

    int currentCharIndex = 0;
    while(currentCharIndex < stringToSplit.size()) {
        char currentChar = stringToSplit.at(currentCharIndex);

        if(currentChar != delimiter) {
            currentToken.push_back(currentChar);
        }

        else {
            string newToken = currentToken;
            tokens.push_back(newToken);
            currentToken = "";
        }
        currentCharIndex++;
    }
    string newToken = currentToken;
    tokens.push_back(newToken);

    return tokens;
}

bool StringLibrary::isParsableToInt(string str) {
    try {
        size_t pos;
        int num = stoi(str, &pos);
        
        return pos == str.size();
    }
    catch (invalid_argument&) {
        return false;
    }
    catch (out_of_range&) {
        return false;
    }
}

string StringLibrary::getIndentedString(string s, int indentCount) {
    if(s == "") return "";

    vector<string> tokens = StringLibrary::splitByDelimiter(s, '\n');

    string indent = "";
    for (int i = 0; i < indentCount; i++)
        indent += " ";

    for(string s : tokens) {
        s = indent + s;
    }
    
    string outputString = "";
    int i;
    for (i = 0; i < tokens.size() - 1; i++)
        outputString += indent + tokens.at(i) + "\n";

    outputString += indent + tokens.at(i);

    return outputString;
}
