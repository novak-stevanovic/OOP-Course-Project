#ifndef DATABASE_H
#define DATABASE_H

#include "item_already_exists_exception.h"
#include "item_doesnt_exist_exception.h"
#include <unordered_map>
#include <vector>

using namespace std;

template <typename K, typename T>
class Database {
private:
    unordered_map<K, T> _items;

public:
    virtual ~Database() {};
    void addItem(K key, T item) {
        if(doesItemExist(key)) 
            throw ItemAlreadyExistsException();

        _items.insert({key, item});
    }

    void removeItem(const K key) {
        if(!doesItemExist(key))
            throw ItemDoesntExistException();

        _items.erase(key);
    }

    T getItemForKey(K key) const {
        if(!doesItemExist(key))
            throw ItemDoesntExistException();

        return _items.at(key);
    }

    bool doesItemExist(const K key) const {
        return (_items.count(key) > 0);
    }

    vector<K> getKeys() const {
        vector<K> keys;
        for (const auto& pair : _items)
            keys.push_back(pair.first);  

        return keys;
    }

    vector<T> getValues() const {
        vector<T> values;
        for (const auto& pair : _items)
            values.push_back(pair.second);  

        return values;
    }

};

#endif
