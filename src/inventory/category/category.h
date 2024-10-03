#ifndef CATEGORY_H
#define CATEGORY_H

#include <list>
#include <string>
#include <vector>

using namespace std;

class Category {

private:
    string _ID;
    string _name;
    vector<Category*> _possibleValues;
    Category* _superCategory;
    bool _selectable;

public:
    Category(string, string, Category*, bool);

    const string getName() const;
    const string getID() const;
    Category* getSuperCategory() const;
    bool hasSuperCategory() const;
    const bool isDescendedFrom(const Category&) const;

    void addPossibleSubcategory(Category*);
    const vector<Category*>& getPossibleSubcategories() const;
    const vector<Category*> getAllSubcategories() const;
    bool hasSubcategory(string) const;
    bool hasSubcategory(Category*) const;

    bool operator==(const Category&) const;
    friend ostream& operator<<(ostream&, const Category&);
    virtual string toString() const;

    bool isSelectable() const;
    void printCategory(list<Category*>, int) const;

};

#endif
