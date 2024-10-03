#include "item_stock_information_object.h"

ItemStockInformationObject::ItemStockInformationObject(double pricePerUnit, double amount) 
    : _pricePerUnit(pricePerUnit), _amount(amount) {}

double ItemStockInformationObject::getPricePerUnit() const {
    return _pricePerUnit;
}

double ItemStockInformationObject::getAmount() const {
    return _amount;
}

void ItemStockInformationObject::setPricePerUnit(double pricePerUnit) {
    _pricePerUnit = pricePerUnit;
}

void ItemStockInformationObject::setAmount(double amount) {
    _amount = amount;
}

ostream& operator<<(ostream& os, const ItemStockInformationObject& object) {
    os << "Amount: " << object._amount << " | " << "Price per unit: " << object._pricePerUnit;
    return os;
}
