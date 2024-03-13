#include "showcollegeswindow.h"
#include "ui_showcollegeswindow.h"
#include "showsouvenirswindow.h" // Used to show souvenirs

showcollegeswindow::showcollegeswindow(DbManager *dbManager, QWidget *parent) :
    QDialog(parent),
    dbManager(dbManager),
    ui(new Ui::showcollegeswindow)
{
    ui->setupUi(this);

    // Configure the table widget
    ui->tableWidget->setColumnCount(2); // Two columns: College and Distance
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "College" << "Distance to Saddleback");
    // Populate the table with colleges and distances
    populateCollegeDistanceTable();

    // Populate the list of colleges
    for (const College& college : dbManager->CollegeVec) {
        ui->listWidget->addItem(college.getCollegeName());
    }

    // Connect the itemClicked signal of the QListWidget to your slot
    connect(ui->listWidget, &QListWidget::itemClicked, this, &showcollegeswindow::on_collegeSelected);
}


showcollegeswindow::~showcollegeswindow()
{
    delete ui;
}

void showcollegeswindow::on_collegeSelected() {
    QListWidgetItem* selectedItem = ui->listWidget->currentItem();
    if (selectedItem) {
        QString collegeName = selectedItem->text();

        // Assuming you have a function in DbManager to find a College object by its name
        College selectedCollege = dbManager->findCollegeByName(collegeName);

        // Assuming you have a constructor for SouvenirListWindow that takes a College object
        ShowSouvenirsWindow souvenirWindow(selectedCollege, this);
        souvenirWindow.exec();  // Show the souvenir window modally
    }
}


void showcollegeswindow::populateCollegeDistanceTable() {
    ui->tableWidget->setRowCount(dbManager->CollegeVec.size()); // Assuming dbManager->CollegeVec contains all colleges

    // int row = 0;
    // for (const College& college : dbManager->CollegeVec) {

    //     double distance = college.getDistanceToSaddleback();

    //     QTableWidgetItem* collegeItem = new QTableWidgetItem(college.getCollegeName());
    //     QTableWidgetItem* distanceItem = new QTableWidgetItem(QString::number(distance) + " mi");

    //     ui->tableWidget->setItem(row, 0, collegeItem);
    //     ui->tableWidget->setItem(row, 1, distanceItem);

    //     row++;
    // }

    // Resize columns to content
    ui->tableWidget->resizeColumnsToContents();
}
