#ifndef SOUVENIR_H
#define SOUVENIR_H

#include <iostream>
#include <string>
#include <QString>
using namespace std;

/**
 * @brief The Souvenir class represents a souvenir item.
 */
class Souvenir {
public:
    /**
     * @brief Constructor for the Souvenir class.
     * @param name The name of the souvenir.
     * @param price The price of the souvenir.
     */
    Souvenir(QString name, double price);

    /**
     * @brief Destructor for the Souvenir class.
     */
    ~Souvenir();

    /**
     * @brief Modifies the price of the souvenir.
     * @param price The new price of the souvenir.
     */
    void modifyPrice(double price);

    /**
     * @brief Gets the name of the souvenir.
     * @return The name of the souvenir.
     */
    QString getName() const;

    /**
     * @brief Gets the price of the souvenir.
     * @return The price of the souvenir.
     */
    double getPrice() const;

    /**
     * @brief Overloaded insertion operator to output Souvenir information.
     * @param out The output stream.
     * @param sovenir The Souvenir object to output.
     * @return The output stream.
     */
    friend ostream& operator << (ostream& out, const Souvenir& sovenir);

private:
    QString name; // holds the name of the souvenir
    double price; // holds the price of the souvenir
};

#endif // SOUVENIR_H
