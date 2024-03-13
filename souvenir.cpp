#include "souvenir.h"

// Creates a souvenir object with the name and price passed in
Souvenir::Souvenir(QString name, double price) : name(name), price(price) {}

Souvenir::~Souvenir(){}

// changes the price of the souvenir to the price passed in
void Souvenir::modifyPrice(double price) {
    this -> price = price;
}

// returns the name of the souvenir
QString Souvenir::getName() const {
    return name;
}

// returns the price of the souvenir
double Souvenir::getPrice() const{
    return price;
}

// Overload the insertion operator to output a souvenir objec
ostream& operator<<(ostream& out, const Souvenir& souvenir) {
    out << "Name: " << souvenir.name.toStdString()
        << ", Price: $" << souvenir.price;
    out << endl;
    return out;
}
