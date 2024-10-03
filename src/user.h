#ifndef USER_H
#define USER_H

#include <list>
#include <string>
#include "inventory/inventory.h"

using namespace std;

class User {

public:
    class UserInformation {
        private:
            string _username;
            string _firstName;
            string _lastName;
            string _password;
            string _phoneNumber;

        public:
            UserInformation(string, string, string, string, string);
            string getUsername() const;
            string getFirstName() const;
            string getLastName() const;
            bool checkPassword(string) const;
            string getPhoneNumber() const;
            friend ostream& operator<<(ostream&, const UserInformation&);
            string toString() const;
    };
    
    class MarketInformation {
        private:
            int _timesSold;
            int _timesBought;
            double _rating;
            double _timesRated;
            double _balance;
        public:
            MarketInformation();
            int getTimesSold() const;
            int getTimesBought() const;
            int getTimesRated() const;
            double getRating() const;
            double getBalance() const;

            void increaseTimesSold();
            void increaseTimesBought();
            void setBalance(double);
            void addRating(double);
            friend ostream& operator<<(ostream&, const MarketInformation&);
            string toString() const;

    };

    User(UserInformation*);
    ~User();

    Inventory& getInventory() const;
    UserInformation& getUserInformation() const;
    MarketInformation& getMarketInformation() const;
    friend ostream& operator<<(ostream&, const User&);
    virtual string toString() const;

    void buyItem(User&, Item*, double);
    bool canBuyItem(User&, Item*, double) const;
    void removeItemFromInventory(Item&);

private:
    Inventory* _inventory;
    UserInformation* _userInformation;
    MarketInformation* _marketInformation;
};

#endif 
