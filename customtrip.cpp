// #include "customtrip.h"
// /* Summary
//  * Constructor customTrip():

// It checks if the default SQL connection exists. If it does, it uses that; otherwise, it creates a new SQLite connection.
// It sets the database name to ./Project.db and attempts to open it, logging the outcome.
// A QSqlQueryModel (commented as a read-only model) is declared but not used.
// A QSqlQuery is set up to select college names from the Custom_Trip table and store them in a vector.
// It iterates through the fetched college names, creating customCollege objects, storing them in a vector, and setting their names.
// Next, it prepares a query to select distances between colleges from a distanceSheet table and populates the corresponding customCollege objects.
// It prints out all the colleges and their distances to the debug console.
// Function fullMap(QString start, int numberOfcolleges):

// It prepares for a trip starting at a specified college, intended to visit a specified number of colleges.
// The database connection is checked and opened similarly to the constructor.
// It locates the starting college and initializes a trip, storing visited colleges in a vector.
// It loops through the number of colleges to visit, calculating the trip's path and accumulating distances.
// It logs each step to the debug console and inserts the trip information into a table ASU_Trip in the database.
// Finally, it clears the colleges and visited vectors.
// Both functions use the QSqlDatabase and QSqlQuery classes to interact with an SQLite database and handle potential connections, queries, and data manipulation. The customCollege structure is used to represent colleges and their connections to other colleges by distance.*/
// customTrip::customTrip()
// {
//     QSqlDatabase myDb;

//     if(QSqlDatabase::contains("qt_sql_default_connection"))
//     {
//         myDb = QSqlDatabase::database("qt_sql_default_connection");
//     }
//     else
//     {
//         myDb = QSqlDatabase::addDatabase("QSQLITE");
//     }

//     myDb.setDatabaseName("./Project.db");
//     if (myDb.open())
//     {
//         qDebug().noquote() << "db found and open";
//     }
//     else
//     {
//         qDebug().noquote() << "db not found";
//     }

//     QSqlQueryModel model; //model is readonly access (query results)
//     QSqlQuery query(myDb);
//     query.prepare("SELECT college FROM Custom_Trip");
//     std::vector<QString> college_names;
//     query.exec();

//     while (query.next())
//      {
//          college_names.push_back(query.value(0).toString());
//      }
//     qDebug().noquote() << "college names fetched";
//     num_of_colleges = int(college_names.size());

//     for (int i=0;i<num_of_colleges;i++)
//     {
//         customCollege* temp = new customCollege;
//         colleges.push_back(temp);
//         colleges[i]->name = college_names[i].toStdString();
//         qDebug().noquote() << QString("college "+QString::fromStdString(colleges[i]->name)+" added");
//     }
//     qDebug().noquote() << "colleges vector filled";

//     for (int i=0;i<num_of_colleges;i++)
//     {
//         query.prepare("SELECT Ending_college,Distance FROM distanceSheet WHERE Starting_college = (:collegename) ORDER BY Distance");
//         query.prepare("SELECT Ending_college,Distance FROM distanceSheet INNER JOIN Custom_Trip WHERE Starting_college = (:collegename) AND Ending_college = college ORDER BY Distance");
//         query.bindValue(":collegename",college_names[i]);
//         query.exec();
//         while(query.next()){
//             for (int j=0;j<num_of_colleges;j++)
//             {
//                 if (query.value(0).toString() == college_names[j])
//                 {
//                     colleges[i]->college_signs.push_back(colleges[j]);
//                     colleges[i]->distances.push_back(query.value(1).toInt());
//                 }
//             }
//         }
//         qDebug().noquote() << QString::fromStdString(colleges[i]->name);
//     }
//     qDebug().noquote() << "All college objects built";

//     for (int j=0;j<num_of_colleges;j++)
//     {
//         qDebug().noquote() << QString::fromStdString(colleges[j]->name);
//         for (int i=0;i<num_of_colleges-1;i++)
//         {
//             qDebug().noquote() << QString::fromStdString(colleges[j]->college_signs[i]->name) << colleges[j]->distances[i];
//         }
//     }
//     distances_travelled.push_back(0);
// }

// void customTrip::fullMap(QString start, int numberOfcolleges)
// {
//     bool incorrectcollege = false;

//     customCollege* current = NULL;
//     QSqlDatabase myDb;
//     int distance=0;
//     QString table = start;

//     QSqlQuery query(myDb);
//     int j = 0;
//     int forLoopcollegeIteration = 0;
//     int initcollege = 0;


//     int collegesVisted = numberOfcolleges; //added this for generalization for other functions

//     if(QSqlDatabase::contains("qt_sql_default_connection"))
//     {
//         myDb = QSqlDatabase::database("qt_sql_default_connection");
//     }
//     else
//     {
//         myDb = QSqlDatabase::addDatabase("QSQLITE");
//     }

//     myDb.setDatabaseName("./Project.db");
//     if (myDb.open())
//     {
//         qDebug().noquote() << "db found and open";
//     }
//     else
//     {
//         qDebug().noquote() << "db not found";
//     }

//     while (!incorrectcollege)
//     {
//         if (QString::fromStdString(colleges[initcollege] -> name) == start)
//         {
//             current = colleges[initcollege];
//             incorrectcollege = true;
//         }
//         else
//         {
//             initcollege++;
//         }

//     }

//     std::string temp = current->college_signs[0]->name;

//     visited.push_back(*current);

//     for (int i = 0; i < numberOfcolleges - 1; i++)
//     {

//         visited.push_back(*current->college_signs[forLoopcollegeIteration]);
//         distance += current->distances[forLoopcollegeIteration];
//         distances_travelled.push_back(distance);

//         temp = current->college_signs[forLoopcollegeIteration]->name;
//         incorrectcollege = false;
//         j=0;
//         forLoopcollegeIteration = 0;

//         while (!incorrectcollege)
//         {
//             if (colleges[j]-> name == temp)
//             {
//                 current = colleges[j]; //setting current to current college on list which
//                                      //is sorted by shortest distance
//                 qDebug().noquote() << QString::fromStdString(current->name);
//                 incorrectcollege = true;
//             }
//             else
//             {
//                 qDebug().noquote() << QString(QString::fromStdString(temp) + " does not match " + QString::fromStdString(colleges[j]->name));
//                 j++;
//             }
//         }

//         if (visited.size() != numberOfcolleges)
//         {
//             for (int visitedTest = 0; visitedTest < int(visited.size()); visitedTest++)
//             {

//                 if (QString::fromStdString(current->college_signs[forLoopcollegeIteration] -> name) == QString::fromStdString(visited[visitedTest].name))
//                 {


//                      ++forLoopcollegeIteration;
//                      visitedTest = 0;
//                 }
//                 if (QString::fromStdString(current->college_signs[forLoopcollegeIteration] -> name) == start)
//                 {
//                      forLoopcollegeIteration++;
//                 }

//                 qDebug().noquote() << " FINAL TEST: " << QString::fromStdString(visited[visitedTest].name) << "current: " << QString::fromStdString(current->college_signs[forLoopcollegeIteration] -> name);
//             }

//         }
//         qDebug().noquote() << QString::fromStdString(temp);
//     }

//     qDebug().noquote() << "SIZE: "<< int(visited.size());
//     for (int i=0;i<collegesVisted;i++)
//     {
//         query.prepare("INSERT INTO ASU_Trip VALUES ((:college),(:distance))");
//         query.bindValue(":college",QString::fromStdString(visited[i].name));
//         query.bindValue(":distance",distances_travelled[i]);
//         query.exec();
//         query.next();
//     }
//     colleges.clear();
//     visited.clear();
// }
