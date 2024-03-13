#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QtSql>
#include <vector>
#include "college.h"

/**
 * @brief The DistanceData struct represents the data structure to hold information about distances between colleges.
 */
struct DistanceData {
    QString startCollege; ///< The name of the starting college.
    QString endCollege;   ///< The name of the ending college.
    double distance;      ///< The distance between the starting and ending colleges.
};

/**
 * @brief The DbManager class is responsible for managing interactions with the SQLite database.
 */
class DbManager
{
public:
    QVector<DistanceData> DistanceVec; ///< A vector holding distance data between colleges.
    QVector<College> CollegeVec;       ///< A vector of College objects representing colleges.

    /**
     * @brief Constructor for the DbManager class.
     * @param path The path to the SQLite database.
     */
    DbManager(const QString& path);

    /**
     * @brief Destructor for the DbManager class.
     */
    ~DbManager();

    /**
     * @brief Checks if the SQLite database is open.
     * @return True if the database is open, false otherwise.
     */
    bool isOpen() const;

    /**
     * @brief Adds colleges and distances from a new SQLite table.
     */
    void addColleges();

    /* REMOVE */
    /**
     * @brief Prints all colleges in the database.
     */
    void printAllColleges() const;

    /**
     * @brief Retrieves the vector of college objects.
     * @return A const reference to the vector of college objects.
     */
    const QVector<College>& getCollegeVec() const;

    QVector<College> specialColleges; ///< A vector holding special colleges.
    void addSouvenirs(const College&);
    /**
     * @brief Retrieves the vector of available colleges.
     * @return A const reference to the vector of available colleges.
     */
    const QVector<College>& getAvailableColleges() const;

private:
    QSqlDatabase m_db;         ///< The SQLite database object.
    QSet<QString> uniqueColleges; ///< Set to store unique college names.

    /**
     * @brief Populates the DistanceVec vector with data about distances between colleges.
     */
    void populateDistanceVec();

    /**
     * @brief Populates the CollegeVec vector with college objects.
     */
    void populateCollegeVec();

    /**
     * @brief Reads souvenirs from a file and adds them to the appropriate college object.
     */
    void readInSouvenirs();

    QString collegeName; ///< The name of the college.
};

#endif // DBMANAGER_H
