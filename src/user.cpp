#include "user.h"
#include <set>

User::UserInformation::UserInformation(string username, string firstName, string lastName, string password, string phoneNumber)
    : _username(username), _firstName(firstName), _lastName(lastName), _password(password), _phoneNumber(phoneNumber) {}

User::~User() {
    delete _inventory;
    delete _userInformation;
    delete _marketInformation;
}

string User::UserInformation::getUsername() const {
    return _username;
}

string User::UserInformation::getFirstName() const {
    return _firstName;
}

string User::UserInformation::getLastName() const {
    return _lastName;
}

bool User::UserInformation::checkPassword(string password) const {
    return _password == password;
}

string User::UserInformation::getPhoneNumber() const {
    return _phoneNumber;
}

User::MarketInformation::MarketInformation() 
    : _timesSold(0), _timesBought(0), _rating(0), _timesRated(0), _balance(0.0) {}

int User::MarketInformation::getTimesSold() const {
    return _timesSold;
}

int User::MarketInformation::getTimesBought() const {
    return _timesBought;
}

int User::MarketInformation::getTimesRated() const {
    return _timesRated;
}

double User::MarketInformation::getRating() const {
    return _rating;
}

double User::MarketInformation::getBalance() const {
    return _balance;
}

void User::MarketInformation::increaseTimesSold() {
    _timesSold++;
}

void User::MarketInformation::increaseTimesBought() {
    _timesBought++;
}

void User::MarketInformation::setBalance(double newBalance) {
    _balance = newBalance;
}

void User::MarketInformation::addRating(double newRating) {
    _rating = ((_timesRated * _rating) + newRating) / (_timesRated+1);
    _timesRated++;
}

User::User(UserInformation* userInformation) 
    : _inventory(new Inventory()), _userInformation(userInformation), _marketInformation(new MarketInformation()) {}

Inventory& User::getInventory() const {
    return *_inventory;
}

User::UserInformation& User::getUserInformation() const {
    return *_userInformation;
}

User::MarketInformation& User::getMarketInformation() const {
    return *_marketInformation;
}

bool User::canBuyItem(User& seller, Item* item, double amount) const {
    return (seller.getInventory().hasInStock(item, amount) && getMarketInformation().getBalance() >= (amount * seller.getInventory().getPrice(item)));
}

void User::buyItem(User& seller, Item* item, double amount) {
    seller.getInventory().changeStockCount(item, -amount);
    double money = seller.getInventory().getPrice(item) * amount;
    seller.getMarketInformation().setBalance(seller.getMarketInformation().getBalance() + money);
    seller.getMarketInformation().increaseTimesSold();
    getMarketInformation().setBalance(getMarketInformation().getBalance() - money);
    getMarketInformation().increaseTimesBought();
}

void User::removeItemFromInventory(Item& item) {
    try {
        getInventory().removeItem(&item);
    }
    catch (const ItemDoesntExistException& e) {
        cout << e.what() << endl;
    }
}

ostream& operator<<(ostream& os, const User::UserInformation& userInformation) {
    os << userInformation.toString();
    return os;
}

ostream& operator<<(ostream& os, const User::MarketInformation& marketInformation) {
    os << marketInformation.toString();
    return os;
}

string User::MarketInformation::toString() const {
    string outputString = "";
    outputString =+ "Times Sold: " + to_string(_timesSold) + "\n"
       + "Times Bought: " + to_string(_timesBought) + "\n"
       + "Rating: " + to_string(_rating) + "\n"
       + "Times Rated: " + to_string(_timesRated) + "\n"
       + "Balance: " + to_string(_balance);
    return outputString;
}

string User::UserInformation::toString() const {
    string outputString = "";
    outputString += "Username: " + _username + "\n"
        + "First Name: " + _firstName + "\n"
        + "Last Name: " + _lastName + "\n"
        + "Phone Number: " + _phoneNumber;
    return outputString;
}

string User::toString() const {
    string outputString = "";
    outputString += _userInformation->getFirstName() + " " +_userInformation->getLastName();
    return outputString;
}

ostream& operator<<(ostream& os, const User& user) {
    os << user.toString();
    return os;
}
