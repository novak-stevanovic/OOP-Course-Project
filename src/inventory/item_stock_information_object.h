#ifndef ITEM_STOCK_INFORMATION_OBJECT_h
#define ITEM_STOCK_INFORMATION_OBJECT_h

#include "iostream"
using namespace std;

class ItemStockInformationObject {
private:
    double _pricePerUnit;
    double _amount;
public:
    ItemStockInformationObject(double, double);
    double getPricePerUnit() const;
    double getAmount() const;
    void setPricePerUnit(double);
    void setAmount(double);

    friend ostream& operator<<(ostream&, const ItemStockInformationObject&);

};

#endif
