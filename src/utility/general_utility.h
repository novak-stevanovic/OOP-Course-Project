#ifndef GENERAL_UTILITY_H
#define GENERAL_UTILITY_H

#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>

using namespace std;

class GeneralUtility {

public:

    template <typename T>
    static bool doesVectorContain(const vector<T>& vector, const T element) {
        for(T vectorElement : vector) {
            if(element == vectorElement)
                return true;
        }

        return false;
    }

    template <typename T>
    static bool doesVectorContain(const vector<T*>& vector, const T& element) {
        for(T* vectorElement : vector) {
            if(element == (*vectorElement))
                return true;
        }

        return false;
    }

    template <typename T>
    static void eraseVectorElement(vector<T>& vec, const T& element) {
        auto it = find(vec.begin(), vec.end(), element);
        if (it != vec.end()) {
            vec.erase(it);
        }
    }

};

#endif
