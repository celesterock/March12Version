#include "mainwindow.h"

#include <QApplication>
#include <QtSql>
#include <QDebug>
#include <QCoreApplication>
#include <dbmanager.h>
#include <visitcollegewindow.h>
#include "TripPlanner.h"
using namespace std;

// change to the path of the database
static const QString path = "C:/Users/donov/AppData/Local/MARCH/CollegeData.db";

int main(int argc, char *argv[])
{
    // Constructor will output an error if database could not be opened
    DbManager db(path);


    QApplication a(argc, argv);
    MainWindow w(&db);
    w.show();
    return a.exec();
}
