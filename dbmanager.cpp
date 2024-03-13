#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QSet>

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection ok\n\n";
        populateDistanceVec();
        populateCollegeVec();
        // addColleges();
        readInSouvenirs();
    }
}

// closes the database
DbManager::~DbManager() {
    m_db.close();
}


/* Uses CollegeDistanceCSV table to read in the list of starting colleges, ending colleges
   and distance between them. Adds this information to DistanceVec
*/
void DbManager::populateDistanceVec() {

    QSqlQuery query;
    query.exec("SELECT * FROM CollegeDistanceCSV");
    int idStart = query.record().indexOf("Starting College");
    int idEnd = query.record().indexOf("Ending College");
    int idDist = query.record().indexOf("Distance Between");

    while (query.next()) {
        QString startCollege = query.value(idStart).toString();
        QString endCollege = query.value(idEnd).toString();
        double distance = query.value(idDist).toDouble();

        DistanceData structInstance;
        structInstance.startCollege = startCollege;
        structInstance.endCollege = endCollege;
        structInstance.distance = distance;
        DistanceVec.push_back(structInstance);
    }
}

/* Creates a vector of College objects which holds every college campus
 * that the student could choose to visit
 */
void DbManager::populateCollegeVec() {
    QSqlQuery collegeQuery;
    collegeQuery.exec("SELECT * FROM CollegeDistanceCSV");
    int idStart = collegeQuery.record().indexOf("Starting College");

    while(collegeQuery.next()) {
        QString collegeName = collegeQuery.value(idStart).toString();

        // Check if the college name has already been encountered
        if (!uniqueColleges.contains(collegeName)) {
            // Add the new college name to the set
            uniqueColleges.insert(collegeName);

            // Create and add new College object
            CollegeVec.push_back(College(collegeName));
        }
    }
}

// DANIEL VERSION
// void DbManager::addColleges(const QString& collegeName) {
//     QSqlQuery query;
//     query.exec("SELECT * FROM NewCampusesCSV");
//     // query.exec("SELECT COUNT(*) FROM NewCampusesCSV");
//     // query.bindValue(0, collegeName);

//     if (!query.exec()) {
//         qDebug() << "Error executing query:" << query.lastError().text();
//         return;
//     }

//     int idStart = query.record().indexOf("Starting College");
//     int idEnd = query.record().indexOf("Ending College");
//     int idDist = query.record().indexOf("Distance Between");

//     while (query.next()) {
//         QString startCollege = query.value(idStart).toString();
//         QString endCollege = query.value(idEnd).toString();
//         double distance = query.value(idDist).toDouble();

//         // Check if the college name has already been encountered
//         if (!uniqueColleges.contains(startCollege)) {
//             uniqueColleges.insert(startCollege);
//             CollegeVec.push_back(College(startCollege));
//         }

//         // Add the distance data to DistanceVec
//         DistanceData structInstance;
//         structInstance.startCollege = startCollege;
//         structInstance.endCollege = endCollege;
//         structInstance.distance = distance;
//         DistanceVec.push_back(structInstance);
//     }

//     qDebug() << "Inside the addColleges Function for college: " << collegeName << "\n";
//     for(const College& college : CollegeVec) {
//         qDebug() << college.getCollegeName(); // Assuming you have a getter for the college name
//     }

//     qDebug() << "************************************************************************\n\n";
// }

/* Takes a file of starting college, ending college, and distance between that
 * the admin wants to add to the program and adds the data to DistanceVec.
 * ALSO adds the new College objects to CollegeVec.
 * */
void DbManager::addColleges() {
    QSqlQuery query;
    query.exec("SELECT * FROM NewCampusesCSV");
    int idStart = query.record().indexOf("Starting College");
    int idEnd = query.record().indexOf("Ending College");
    int idDist = query.record().indexOf("Distance Between");

    // add information to DistanceVec
    while (query.next()) {
        QString startCollege = query.value(idStart).toString();
        QString endCollege = query.value(idEnd).toString();
        double distance = query.value(idDist).toDouble();

        DistanceData structInstance;
        structInstance.startCollege = startCollege;
        structInstance.endCollege = endCollege;
        structInstance.distance = distance;
        DistanceVec.push_back(structInstance);
    }

    QSqlQuery collegeQuery;
    collegeQuery.exec("SELECT * FROM NewCampusesCSV");
    idStart = collegeQuery.record().indexOf("Starting College");

    // Add colleges to CollegeVec
    while(collegeQuery.next()) {
        QString collegeName = collegeQuery.value(idStart).toString();

        // Check if the college name has already been encountered
        if (!uniqueColleges.contains(collegeName)) {
            // Add the new college name to the set
            uniqueColleges.insert(collegeName);
            // Create and add new College object
            CollegeVec.push_back(College(collegeName));
        }
    }
}

/* Reads in the souvenir name and price from SouvenirCSV and adds the souvenir data
 * to the appropriate College object in CollegeVec
 **/
void DbManager::readInSouvenirs() {

    QString currentCollegeName;
    College* currentCollege = nullptr;

    QSqlQuery souvenirQuery("SELECT * FROM SouvenirCSV");
    while(souvenirQuery.next()) {
        int idCollegeName = souvenirQuery.record().indexOf("College");
        int idTraditionalSouvenirs = souvenirQuery.record().indexOf("Traditional Souvenirs");
        int idPrice = souvenirQuery.record().indexOf("Cost");

        // Extract the college name, souvenir name, and price from each row
        QString collegeName = souvenirQuery.value(idCollegeName).toString();
        QString souvenirName = souvenirQuery.value(idTraditionalSouvenirs).toString();
        QString souvenirPrice = souvenirQuery.value(idPrice).toString();

        // Check if college name is empty and find the corresponding college object
        if(!collegeName.isEmpty() && collegeName != currentCollegeName) {
            // Find the corresponding college in CollegeVec for the current souvenir
            // 'it' will be a QVector<College>::iterator
            auto it = find_if(CollegeVec.begin(), CollegeVec.end(), [&collegeName](const College& college) {
                return college.getCollegeName() == collegeName;
            });

            // Only set currentCollege if the college is found in CollegeVec
            currentCollege = (it != CollegeVec.end()) ? &(*it) : nullptr;

            // Update the name of the last processed college
            currentCollegeName = collegeName;
        }

        if(currentCollege && !souvenirName.isEmpty()) {
            // need to take of the $ on the price and convert to a double
            double cost = souvenirPrice.remove(0,1).toDouble();

            // souvenir object that will be added to the Souvenir vector attribute of the college
            currentCollege->addSouvenir(Souvenir(souvenirName, cost));
        }
    }
}

void DbManager::addSouvenirs(const College& update)
{
    auto it = find_if(CollegeVec.begin(), CollegeVec.end(), [&update](const College& college) {
        return college.getCollegeName() == update.getCollegeName();
    });

    if (it != CollegeVec.end())
    {
        const QVector<Souvenir>& newSouvenirs = update.getSouvenirOptions();
        for (const Souvenir& newSouvenir : newSouvenirs) {
            it->addSouvenir(newSouvenir);
        }
    }
    else
    {

    }
    qDebug() << "Inside the addSouvenirs Function for college: " << it->getCollegeName() << "\n";
    for(const Souvenir& souvenir : it->getSouvenirOptions()) {
        qDebug() << "Name of Souvenir: " << souvenir.getName() << "\t Prices: " << souvenir.getPrice() << "\n"; // Assuming you have a getter for the college name
    }

    qDebug() << "************************************************************************\n\n";

}

// returns true if Database was successfully opened
bool DbManager::isOpen() const {
    return m_db.isOpen();
}

// returns CollegeVec
const QVector<College>& DbManager::getCollegeVec() const {
    return CollegeVec;
}

const QVector<College>& DbManager::getAvailableColleges() const {
    return specialColleges;
}

/* REMOVE */
void DbManager::printAllColleges() const {
    qDebug() << "Colleges in Database: \n\n";
    QSqlQuery query("SELECT * FROM CollegeDistanceCSV");

    if (!query.isActive()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    int idField1 = query.record().indexOf("Starting College");

    if (idField1 == -1) {
        qDebug() << "Field 'Starting College' not found.";
        return;
    }

    qDebug() << "before while loop\n\n";
    while(query.next()) {
        QString name = query.value(idField1).toString();
        qDebug() << " === " << name;
        qDebug() << "in while loop\n\n";
    }
    qDebug() << "after while loop\n\n";
}

College DbManager::findCollegeByName(QString name) {
    for (const College& college : CollegeVec) {
        if (college.getCollegeName().compare(name, Qt::CaseInsensitive) == 0) {
            return college;  // Found a matching college, return it
        }
    }

    // No matching college found, return a default College object or handle as needed
    return College();
}


double DbManager::getDistanceToSaddleback(College collegeName) {
    QString saddlebackName = "Saddleback College";

    for (const DistanceData& data : DistanceVec) {
        // Ensure that you compare QString to QString
        if ((data.startCollege == collegeName.getCollegeName() && data.endCollege == saddlebackName) ||
            (data.startCollege == saddlebackName && data.endCollege == collegeName.getCollegeName())) {
            return data.distance;
        }
    }

    return -1;
}
