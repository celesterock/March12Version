#ifndef SOUVENIR_H
#define SOUVENIR_H

#include <iostream>
#include <string>
#include <QString>
using namespace std;


class Souvenir {
public:
    /* CONSTRUCTOR AND DESTRUCTOR */
    Souvenir(QString name, double price);
    ~Souvenir();

    // changes the price attribute to the value passed in
    void modifyPrice(double price);

    // returns the name attribute
    QString getName() const;

    // returns the price attribute
    double getPrice() const;

    // overloaded insertion operator
    friend ostream& operator << (ostream& out, const Souvenir& sovenir);

private:
    QString name; // holds the name of the souvenir
    double price; // holds the price of the souvenir
};

#endif // SOUVENIR_H
