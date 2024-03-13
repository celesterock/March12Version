#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adminDialog.h"
#include <CollegeListWindow.h>
#include <visitcollegewindow.h>
#include <dbmanager.h>
#include "showcollegeswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(DbManager* dbManager, QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DbManager* dbManager; // pointer to DbManager instance
    CollegeList *collegeListWindow = nullptr; // pointer to the college list window
    adminDialog* newAdminDialog;

    QMenu* administrativeAccess;

    QAction* toLoginAct;


    void createMenus();
    void createActions();

    // New functions 3/12
    void createCorrectTripOrder(TripPlanner* trip);




private slots:
    void openCollegeListWindow();
    void beginTrip();
    void toLogin();


};
#endif // MAINWINDOW_H
