#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QtSql>
#include <vector>
#include "college.h"
// #include <adminDialog.h>

struct DistanceData {
    QString startCollege;
    QString endCollege;
    double  distance;
};

/* DbManager class is used to read in data from the SQLite database
 *   and store the information in the appropriate structures
 * */
class DbManager
{
public:
    QVector <DistanceData> DistanceVec; // Holds the start college obj, end college obj, and dist btw
    QVector <College> CollegeVec;       // A vector of College objects

    DbManager(const QString& path);     // Constructor; takes in path to the SQLite database
    ~DbManager();

    // Checks that the SQLite database was successfully opened
    bool isOpen() const;

    // adds colleges/distances from a new SQLite table
    void addColleges();

    /* REMOVE */
    void printAllColleges() const;

    // returns the vector of college objects
    const QVector<College>& getCollegeVec() const;

    // Methods added from Daniel
    QVector <College> specialColleges;
    void addSouvenirs(const College&);
    const QVector<College>& getAvailableColleges() const;

private:
    QSqlDatabase m_db;
    QSet<QString> uniqueColleges; // Keeps track of unique college names

    /* Creates a vector of starting college, ending college, and distance between
     * for every college in the file */
    void populateDistanceVec();

    // Adds every unique college (as a College object) to the CollegeVec
    void populateCollegeVec();

    /* Reads in the souvenir file and adds the souvenirs/prices to the
     * appropriate college object */
    void readInSouvenirs();

    // Added from Daniel
    QString collegeName;

};

#endif // DBMANAGER_H
