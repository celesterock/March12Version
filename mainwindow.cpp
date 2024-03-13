#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DbManager* dbManager, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbManager(dbManager)
{
    ui->setupUi(this);

    newAdminDialog = new adminDialog(dbManager, this);
    createActions();
    createMenus();

    // Begin Trip opens the TripPlanner.ui window
    connect(ui->beginTrip, &QPushButton::clicked, this, &MainWindow::beginTrip);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions()
{
    toLoginAct = new QAction("&Login",this);
    connect(toLoginAct, &QAction::triggered, this, &MainWindow::toLogin);
    qDebug() << "hello";

}
void MainWindow::createMenus()
{
    administrativeAccess = menuBar()->addMenu("Admin");
    administrativeAccess->addAction(toLoginAct);
}

void MainWindow::toLogin()
{
    qDebug() << "Login action triggered";
    newAdminDialog->show();
}

/* *************************************************************************
 * Creates a new trip instance and allows the user to make purchases at
 *  every college included in the trip. For now, I have hardcoded 3 colleges.
 * *************************************************************************/
void MainWindow::beginTrip() {

    // Create a new instance of the TripPlanner dialog
    TripPlanner* tripPlanner = new TripPlanner(dbManager, this); // 'this' sets MainWindow as the parent of the dialog

    // Display the TripPlanner dialog
    tripPlanner->exec(); // Use exec() for a modal dialog
    // or tripPlanner->show(); // Use show() for a non-modal window

    // Optional: If you used 'new' without 'exec()', you might want to manage the deletion of tripPlanner to avoid memory leaks
    // If 'exec()' is used, 'tripPlanner' can be safely deleted after 'exec()' because the dialog becomes blocking and remains open until closed by the user
    delete tripPlanner; // Only necessary if 'show()' is used and you want to manage memory manually
    // // Create a new trip
    // TripPlanner* trip = new TripPlanner;

    // createCorrectTripOrder(trip);

    // trip->visitCampus();
}

void MainWindow::createCorrectTripOrder(TripPlanner* trip) {
    /* This will need to change once the trip stories have been finished.
     * For now, I am hard coding to test functionality */
    trip->addCollege(dbManager->getCollegeVec()[0]);
    trip->addCollege(dbManager->getCollegeVec()[1]);
    trip->addCollege(dbManager->getCollegeVec()[2]);
}
