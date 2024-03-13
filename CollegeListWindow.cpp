#include "CollegeListWindow.h"
#include "ui_CollegeListWindow.h"

CollegeList::CollegeList(DbManager *dbManager, QWidget *parent)
    : QDialog(parent),
    dbManager(dbManager),
    ui(new Ui::CollegeList)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(dbManager->CollegeVec.size());
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    connect(ui->beginTrip, &QPushButton::clicked, this, &CollegeList::BeginTripClicked);
    // Populate the list of colleges when the dialog is constructed
    populateListofColleges();
}


CollegeList::~CollegeList()
{
    delete ui;
}

void CollegeList::populateListofColleges() {

    int counter = 1; // Start numbering from 1
    for (const College& college : dbManager->CollegeVec) {
        QString itemText = QString::number(counter) + ". " + college.getCollegeName(); // Format: "1. College Name"
        ui->listWidget->addItem(itemText);
        counter++; // Increment the counter for the next item
    }
}



College CollegeList::findCollegeByName(const QString& name) {
    for (const College& college : dbManager->CollegeVec) {
        if (college.getCollegeName() == name) {
            return college;
        }
    }

    // Handle the case where the college is not found. This might involve returning a default College object
    // or throwing an exception, depending on how you want to handle this scenario.
    return College();  // Returning a default College object. You might want to handle this case differently.
}


QVector<College> CollegeList::getSelectedColleges() {
    QVector<College> selectedColleges;
    QList<QListWidgetItem*> selectedItems = ui->listWidget->selectedItems();

    for (QListWidgetItem* item : selectedItems) {
        QString collegeName = item->text().section(". ", 1, 1); // Assuming the format "1. College Name"
        College college = findCollegeByName(collegeName); // Implement findCollegeByName accordingly
        selectedColleges.append(college);
    }
    return selectedColleges;
}

void CollegeList::BeginTripClicked() {
    int index = ui->spinBox->value() - 1;
    startingCollege = dbManager->CollegeVec[index];
    accept();
}

College CollegeList::getStartingCollege() {
    return startingCollege;
}


