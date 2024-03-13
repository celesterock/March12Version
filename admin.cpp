#include "admin.h"
#include "ui_admin.h"
#include "admin.h"
#include <QMessageBox>
#include "admin.h"

/*
Admin constructor initializes the Admin object with the provided username and password
getUsername function returns the username of the admin
getPassword function returns the password of the admin
setUsername function sets the username of the admin
setPassword function sets the password of the admin
*/

Admin::Admin(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::Admin)
{
   ui->setupUi(this);
}

Admin::~Admin()
{
   delete ui;
}


void Admin::on_addCollegeButton_clicked()
{

   QString startCollege = ui->collegeLineEdit->text();
   QString endingCollege = ui->endingCollegeLineEdit->text();
   QString distance = ui->kilometerLineEdit->text();

   if (startCollege == "" || endingCollege == "" || distance == "")
   {
       QMessageBox::warning(this, "Empty field", "One of your fields is empty");
   }

   QSqlQuery query;
   QSqlQueryModel* qryModel = new QSqlQueryModel();

   query.prepare("INSERT INTO distanceSheet(Starting_College, Ending_College, Distance) VALUES (:Starting, :Ending, :Distance)");
   query.bindValue(":Starting", startCollege);
   query.bindValue(":Ending", endingCollege);
   query.bindValue(":Distance", distance);

   if (!query.exec() )
   {
        QMessageBox::warning(this, "Query Error", "Query not executed");
   }
   else
   {
        QMessageBox::information(this, "College Successfully Added", "Success");

   }

   ui->distanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->distanceTableView->setAlternatingRowColors(true);

   qryModel->setQuery("SELECT Starting_College, Ending_College, Distance FROM distanceSHEET ORDER BY Starting_College DESC, Distance");
   ui->distanceTableView->setModel(qryModel);

}

void Admin::on_addSouvenirButton_clicked()
{
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    QSqlRecord record;
    QSqlQuery searchQuery(myDb);
    QSqlQueryModel searchQryModel;

    QString college = ui->collegeLineEdit2->text();
    QString souvenir = ui->souvenirLineEdit->text();
    std::string quantityString;
    QString cost = ui->costLineEdit->text();
    bool confirmInt;
    bool confirmString = false;

    quantityString = ui->costLineEdit->text().toStdString();

    if (college == "" || souvenir == "" || cost == "")
    {
        QMessageBox::warning(this, "Empty field", "One of your fields is empty");
    }
    else
    {
        for (char const ch : quantityString)
        {
            if(std::isdigit(ch) == 0)
            {
                confirmInt = false;
            }
            else
            {
                confirmInt = true;
            }
        }
        if (confirmInt == true)
        {
            searchQuery.exec("SELECT DISTINCT Starting_College FROM distanceSheet");
            searchQryModel.setQuery(std::move(searchQuery));
            int i = 0;

            while (i < searchQryModel.rowCount() && !confirmString)
            {
                record = searchQryModel.record(i);
                if (college == record.value(0).toString())
                {
                    confirmString = true;
                }
                i++;
            }

            if (confirmString == true)
            {
                QSqlQuery query;
                QSqlQueryModel* qryModel = new QSqlQueryModel();

                query.prepare("INSERT INTO SouvenirSheet(College, Traditional_Souvenir_Item, Cost) VALUES (:College, :Souvenir, :Cost)");
                query.bindValue(":College", college);
                query.bindValue(":Souvenir", souvenir);
                query.bindValue(":Cost", cost);

                if (!query.exec() )
                {
                      QMessageBox::warning(this, "Query Error", "Query not executed");
                }
                else
                {
                      QMessageBox::information(this, "College Successfully Added", "Success");
                }

                ui->souvenirTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->souvenirTableView->setAlternatingRowColors(true);

                qryModel -> setQuery("SELECT SouvenirSheet.College,SouvenirSheet.Traditional_Souvenir_Item as 'Traditional Souvenir Item',SouvenirSheet.Cost FROM SouvenirSheet ORDER BY SouvenirSheet.College");

                ui->souvenirTableView->setModel(qryModel);
            }
            else
            {
                QMessageBox::warning(this, "NOT A College", "enter a College");
            }

        }
        else
        {
            QMessageBox::warning(this, "NOT AN INT", "enter an int into quantity");
        }
    }
}

void Admin::on_initStartingCollegesPushButton_clicked()
{
    QFile file("./CollegeDistances.txt");
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }
    myDb.open();

    QTextStream inFile(&file);
    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qCritical()<<"please make sure that you put the .txt files in debug folder!";
        qCritical()<<file.errorString();
        return;
    }

    QString startString;
    QString endString;
    QString distanceString;
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    while(!inFile.atEnd())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO distanceSheet(Starting_College, Ending_College, Distance) VALUES (:Starting, :Ending, :Distance)");

        startString = inFile.readLine();
        endString = inFile.readLine();
        distanceString = inFile.readLine();

        query.bindValue(":Starting", startString);
        query.bindValue(":Ending", endString);
        query.bindValue(":Distance", distanceString.toInt());
        qDebug() << startString << endString << distanceString;
        query.exec();
    }
    file.close();


    ui->distanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->distanceTableView->setAlternatingRowColors(true);

    qryModel->setQuery("SELECT Starting_College, Ending_College, Distance FROM distanceSHEET ORDER BY Starting_College DESC, Distance");
    ui->distanceTableView->setModel(qryModel);

}

void Admin::on_initNewCollegesPushButton_clicked()
{
    QFile file("./NewCollegesUpload.txt"); //NO SQL JUST TXT FILES
    QTextStream inFile(&file);

    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }
    QSqlQuery *newTableQuery = new QSqlQuery(myDb);
    QSqlQueryModel* qryModel = new QSqlQueryModel();
    myDb.open();

    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
        {
            qCritical()<<"please make sure that you put the .txt files in debug folder!";
            qCritical()<<file.errorString();
            return;
        }

        QString startString;
        QString endString;
        QString distanceString;

        while(!inFile.atEnd())
        {
             QSqlQuery query;
             query.prepare("INSERT INTO distanceSheet(Starting_College, Ending_College, Distance) VALUES (:Starting, :Ending, :Distance)");

             startString = inFile.readLine();
             endString = inFile.readLine();
             distanceString = inFile.readLine();

             query.bindValue(":Starting", startString);
             query.bindValue(":Ending", endString);
             query.bindValue(":Distance", distanceString.toInt());
             qDebug() << startString << endString << distanceString;
             query.exec();

         }
         file.close();

         newTableQuery->exec("CREATE TABLE newDistanceTable as SELECT Starting_College, Ending_College, Distance FROM distanceSheet ORDER BY Starting_College DESC, Distance");
         newTableQuery->exec("DROP TABLE distanceSheet");
         newTableQuery->exec("ALTER TABLE newDistanceTable RENAME To distanceSheet");

         ui->distanceTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
         ui->distanceTableView->setAlternatingRowColors(true);

         qryModel->setQuery("SELECT Starting_College, Ending_College, Distance FROM distanceSHEET ORDER BY Starting_College DESC, Distance");
         ui->distanceTableView->setModel(qryModel);

}


void Admin::on_InitializeStartingSouvenirsPushButton_clicked()
{
    QFile file("./SouvenirsTextFile.txt");
    QTextStream inFile(&file);

    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qCritical()<<"please make sure that you put the .txt files in debug folder!";
        qCritical()<<file.errorString();
        return;
    }

    QString collegeString;
    QString souvenirString;
    QString costString;
    double costDouble;
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    while(!inFile.atEnd())
    {
         QSqlQuery query;
         query.prepare("INSERT INTO SouvenirSheet(College, Traditional_Souvenir_Item, Cost) VALUES (:College, :Souvenir, :Cost)");

         collegeString = inFile.readLine();
         souvenirString = inFile.readLine();
         costString = inFile.readLine();
         costDouble = costString.toDouble();

         query.bindValue(":College", collegeString);
         query.bindValue(":Souvenir", souvenirString);
         query.bindValue(":Cost", costDouble);
         qDebug() << collegeString << souvenirString << costDouble;
         query.exec();

     }
     file.close();

     ui->souvenirTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->souvenirTableView->setAlternatingRowColors(true);

     qryModel -> setQuery("SELECT SouvenirSheet.College,SouvenirSheet.Traditional_Souvenir_Item as 'Traditional Souvenir Item',SouvenirSheet.Cost FROM SouvenirSheet ORDER BY SouvenirSheet.College");

     ui->souvenirTableView->setModel(qryModel);
}


void Admin::on_InitializeNewSouvenirsPushButton_clicked()
{
    QFile file("./NewSouvenirsTextFile.txt");
    QTextStream inFile(&file);

    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }
    myDb.open();

    if (!file.open(QIODevice::OpenModeFlag::ReadOnly))
    {
        qCritical()<<"please make sure that you put the .txt files in debug folder!";
        qCritical()<<file.errorString();
        return;
    }

    QSqlQuery *newTableQuery = new QSqlQuery(myDb);
    QSqlQueryModel* qryModel = new QSqlQueryModel();

    QString collegeString;
    QString SouvenirString;
    QString costString;
    double costDouble;

    while(!inFile.atEnd())
    {
        QSqlQuery query;
        query.prepare("INSERT INTO SouvenirSheet(College, Traditional_Souvenir_Item, Cost) VALUES (:College, :Souvenir, :Cost)");

        collegeString = inFile.readLine();
        SouvenirString = inFile.readLine();
        costString = inFile.readLine();
        costDouble = costString.toDouble();

        query.bindValue(":College", collegeString);
        query.bindValue(":Souvenir", SouvenirString);
        query.bindValue(":Cost", costDouble);
        qDebug() << collegeString << SouvenirString << costDouble;
        query.exec();

     }
     file.close();


     newTableQuery->exec("CREATE TABLE newSouvenirTable as SELECT College, Traditional_Souvenir_Item, Cost FROM SouvenirSheet ORDER BY College");
     newTableQuery->exec("DROP TABLE SouvenirSheet");
     newTableQuery->exec("ALTER TABLE newSouvenirTable RENAME To SouvenirSheet");

     ui->souvenirTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     ui->souvenirTableView->setAlternatingRowColors(true);

     qryModel -> setQuery("SELECT SouvenirSheet.College,SouvenirSheet.Traditional_Souvenir_Item as 'Traditional Souvenir Item',SouvenirSheet.Cost FROM SouvenirSheet ORDER BY SouvenirSheet.College");

     ui->souvenirTableView->setModel(qryModel);
}


void Admin::on_deleteTablePushButton_clicked()
{
    QSqlDatabase myDb;

    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    QSqlQuery *deleteQuery = new QSqlQuery(myDb);

    deleteQuery->exec("DELETE FROM Saddleback_trip");
    deleteQuery->exec("DELETE FROM Custom_Trip");
    deleteQuery->exec("DELETE FROM distanceSheet");
    deleteQuery->exec("DELETE FROM SouvenirSheet");
    deleteQuery->exec("DELETE FROM totalAmountPerCollege");
    deleteQuery->exec("DELETE FROM travelSale");
}

void Admin::on_editSouvenirButton_clicked()
{
    QSqlDatabase myDb;

    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    QSqlRecord record;
    QSqlQuery searchQuery(myDb);
    QSqlQueryModel searchQryModel;
    std::string priceString;

    QString college = ui->collegeLineEdit2->text();
    QString souvenir = ui->souvenirLineEdit->text();
    QString price = ui->costLineEdit->text();

    bool confirmDouble;
    bool confirmString = false;

    priceString = ui->costLineEdit->text().toStdString();

    if (college == "" || souvenir == "" || price == "")
    {
        QMessageBox::warning(this, "Empty field", "One of your fields is empty");
    }
    else
    {
        for (char const ch : priceString)
        {
            if (std::isdigit(ch) == 0 && ch != '.')
            {
                confirmDouble = false;
                break;
            }
            else
            {
                confirmDouble = true;
            }
        }
        if (confirmDouble == true)
        {
            searchQuery.exec("SELECT DISTINCT name FROM colleges");
            searchQryModel.setQuery(std::move(searchQuery));
            int i = 0;
            while (i < searchQryModel.rowCount() && !confirmString)
            {
                record = searchQryModel.record(i);
                if (college == record.value(0).toString())
                {
                    confirmString = true;
                }
                i++;
            }

            if (confirmString == true)
            {
                QSqlQuery query;
                QSqlQueryModel* qryModel = new QSqlQueryModel();

                query.prepare("UPDATE souvenirs SET price = :price WHERE college = :college AND souvenir = :souvenir");
                query.bindValue(":college", college);
                query.bindValue(":souvenir", souvenir);
                query.bindValue(":price", price);

                if (!query.exec())
                {
                    QMessageBox::warning(this, "Query Error", "Query not executed");
                }
                else
                {
                    QMessageBox::information(this, "Souvenir Successfully Updated", "Success");
                }

                ui->souvenirTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->souvenirTableView->setAlternatingRowColors(true);

                qryModel->setQuery("SELECT college, souvenir, price FROM souvenirs ORDER BY college");
                ui->souvenirTableView->setModel(qryModel);
            }
            else
            {
                QMessageBox::warning(this, "NOT A College", "Enter a valid college");
            }
        }
        else
        {
            QMessageBox::warning(this, "NOT A DOUBLE", "Enter a valid price");
        }
    }
}

void Admin::on_deleteSouvenir_clicked()
{
    QSqlDatabase myDb;

    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        myDb = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        myDb = QSqlDatabase::addDatabase("QSQLITE");
    }

    QSqlRecord record;
    QSqlQuery searchQuery(myDb);
    QSqlQueryModel searchQryModel;

    QSqlRecord record2;
    QSqlQuery searchQuery2(myDb);
    QSqlQueryModel searchQryModel2;

    QString college = ui->collegeLineEdit2->text();
    QString souvenir = ui->souvenirLineEdit->text();
    bool confirmCollege = false;
    bool confirmSouvenir = false;

    if (college == "" || souvenir == "") {
        QMessageBox::warning(this, "Empty field", "One of your fields is empty");
    } else {
        searchQuery.exec("SELECT DISTINCT name FROM colleges");
        searchQryModel.setQuery(std::move(searchQuery));
        int i = 0;

        while (i < searchQryModel.rowCount() && !confirmCollege) {
            record = searchQryModel.record(i);
            if (college == record.value(0).toString()) {
                confirmCollege = true;
            }
            i++;
        }

        if (confirmCollege == true) {
            searchQuery2.exec("SELECT DISTINCT souvenir FROM souvenirs");
            searchQryModel2.setQuery(std::move(searchQuery2));
            int j = 0;

            while (j < searchQryModel2.rowCount() && !confirmSouvenir) {
                record2 = searchQryModel2.record(j);
                if (souvenir == record2.value(0).toString()) {
                    confirmSouvenir = true;
                    qDebug().noquote() << "Souvenir found";
                }
                j++;
            }

            if (confirmSouvenir == true) {
                QSqlQuery query;
                QSqlQueryModel* qryModel = new QSqlQueryModel();

                query.prepare("DELETE FROM souvenirs WHERE college = :college AND souvenir = :souvenir");
                query.bindValue(":college", college);
                query.bindValue(":souvenir", souvenir);
                query.exec();

                if (!query.exec()) {
                    QMessageBox::warning(this, "Query Error", "Query not executed");
                } else {
                    QMessageBox::information(this, "Souvenir Successfully Deleted", "Success");
                }

                ui->souvenirTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                ui->souvenirTableView->setAlternatingRowColors(true);

                qryModel->setQuery("SELECT college, souvenir, price FROM souvenirs ORDER BY college");
                ui->souvenirTableView->setModel(qryModel);
            } else {
                QMessageBox::warning(this, "WRONG Souvenir", "Enter a valid souvenir");
            }
        } else {
            QMessageBox::warning(this, "WRONG College", "Enter a valid college");
        }
    }
}
