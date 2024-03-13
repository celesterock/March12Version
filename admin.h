#ifndef ADMIN_H
#define ADMIN_H

//#include "user.h"
#include <QMainWindow>
#include <QListWidget>
#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

// The Admin class inherits from QMainWindow and is used to manage the administrator interface of the application.
// It allows for operations such as adding colleges, souvenirs, initializing data from text files, and deleting tables.

namespace Ui
{
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr); // Constructor
    ~Admin(); // Destructor

private slots:
    // Slot to handle the event when the 'Add College' button is clicked.
    // It triggers the logic to add a new college to the database.
    void on_addCollegeButton_clicked();

    // Slot to handle the event when the 'Add Souvenir' button is clicked.
    // It triggers the logic to add a new souvenir for a specific college to the database.
    void on_addSouvenirButton_clicked();

    // Slot to handle the event when the 'Initialize Starting Colleges' button is clicked.
    // It triggers the logic to load initial college data from a text file into the database.
    void on_initStartingCollegesPushButton_clicked();

    // Slot to handle the event when the 'Initialize New Colleges' button is clicked.
    // It triggers the logic to add new colleges from a text file to the database.
    void on_initNewCollegesPushButton_clicked();

    // Slot to handle the event when the 'Initialize Starting Souvenirs' button is clicked.
    // It triggers the logic to load initial souvenir data from a text file into the database.
    void on_InitializeStartingSouvenirsPushButton_clicked();

    // Slot to handle the event when the 'Initialize New Souvenirs' button is clicked.
    // It triggers the logic to add new souvenirs from a text file to the database.
    void on_InitializeNewSouvenirsPushButton_clicked();

    // Slot to handle the event when the 'Delete Tables' button is clicked.
    // It triggers the logic to delete all data from the application's tables, effectively resetting the database.
    void on_deleteTablePushButton_clicked();

    // Slot to handle the event when the 'Edit Souvenir' button is clicked.
    // It allows the admin to modify the details of an existing souvenir in the database.
    void on_editSouvenirButton_clicked();

    // Slot to handle the event when the 'Delete Souvenir' button is clicked.
    // It allows the admin to remove a specific souvenir from the database.
    void on_deleteSouvenir_clicked();

private:
    Ui::Admin *ui; // Pointer to the UI elements of the admin interface
    QSqlDatabase myDb; // Database connection used by the admin interface
//    user* userWindow = NULL; // Pointer to a user window, allowing admin to switch to user view
};

#endif // ADMIN_H
