#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admin.h" // Include the Admin header

MainWindow::MainWindow(DbManager* dbManager, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dbManager(dbManager),
    adminWindow(nullptr) // Initialize the adminWindow pointer
{
    ui->setupUi(this);

    newAdminDialog = new adminDialog(dbManager, this);
    adminWindow = new Admin(this); // Initialize the Admin window here
    createActions();
    createMenus();

    // Connect the openAdminButton click signal to the appropriate slot (assuming the button is named openAdminButton)
    connect(ui->openAdminButton, &QPushButton::clicked, this, &MainWindow::openAdminWindow);

    // Begin Trip opens the TripPlanner.ui window
    connect(ui->beginTrip, &QPushButton::clicked, this, &MainWindow::beginTrip);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete adminWindow; // Ensure we delete the adminWindow to avoid memory leaks
    delete newAdminDialog;
}

void MainWindow::createActions()
{
    toLoginAct = new QAction("&Login", this);
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

void MainWindow::openAdminWindow()
{
    if (adminWindow) // Check if the Admin window exists
    {
        adminWindow->show(); // If it does, show the Admin window
    }
}

void MainWindow::beginTrip()
{
    // Create a new instance of the TripPlanner dialog
    TripPlanner* tripPlanner = new TripPlanner(dbManager, this);
    // Display the TripPlanner dialog
    tripPlanner->exec();
    delete tripPlanner;
}

void MainWindow::createCorrectTripOrder(TripPlanner* trip)
{
    trip->addCollege(dbManager->getCollegeVec()[0]);
    trip->addCollege(dbManager->getCollegeVec()[1]);
    trip->addCollege(dbManager->getCollegeVec()[2]);
}
