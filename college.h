#ifndef COLLEGE_H
#define COLLEGE_H

#include "souvenir.h"
#include <vector>
#include <iostream>
#include <string>
#include <QString>
#include <QDebug>

/**
 * @brief The College class represents a college institution.
 */
class College {

public:
    /**
     * @brief Default constructor for the College class.
     */
    College();

    /**
     * @brief Parameterized constructor for the College class.
     * @param name The name of the college.
     */
    College(QString name);

    /**
     * @brief Destructor for the College class.
     */
    ~College();

    /**
     * @brief Getter function to retrieve the name of the college.
     * @return The name of the college.
     */
    QString getCollegeName() const;

    /**
     * @brief Setter function to set the name of the college.
     * @param name The name of the college.
     */
    void setName(QString name);

    /**
     * @brief Function to add a souvenir to the college.
     * @param souvenirToAdd The souvenir to add.
     */
    void addSouvenir(Souvenir souvenirToAdd);

    /**
     * @brief Function to get the souvenir options available at the college.
     * @return A QVector of Souvenir objects representing the souvenir options.
     */
    QVector<Souvenir> getSouvenirOptions() const;

    // void deleteSouvenir(string souvenirToDelete);
    // void modifySouvenirPrice(string souvenirToModify, double newPrice);

    friend std::ostream& operator<<(std::ostream& out, const College& college);

private:
    QString name; ///< The name of the college
    QVector<Souvenir> souvenirList; ///< The list of souvenirs available at the college

    /**
     * @brief Function to find the index of a souvenir in the souvenir list by its name.
     * @param souvenirName The name of the souvenir to find.
     * @return The index of the souvenir in the souvenir list.
     */
    int findSouvenirIndex(const QString& souvenirName);

};

#endif // COLLEGE_H
