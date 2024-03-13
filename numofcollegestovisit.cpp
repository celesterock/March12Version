#include "numofcollegestovisit.h"
#include "ui_numofcollegestovisit.h"


NumOfCollegesToVisit::NumOfCollegesToVisit(DbManager* dbManager, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::NumOfCollegesToVisit),
      dbManager(dbManager)
{
    ui->setupUi(this);

    ui->spinBox->setMinimum(1);  // Assuming the user must select at least 1 college
    ui->spinBox->setMaximum(dbManager->CollegeVec.size()); // User cannot visit more colleges than are available
    connect(ui->okButton, &QPushButton::clicked, this, &NumOfCollegesToVisit::okButton);

}

NumOfCollegesToVisit::~NumOfCollegesToVisit()
{
    delete ui;
}

int NumOfCollegesToVisit::getNumberOfColleges() const {
    return ui->spinBox->value();
}

void NumOfCollegesToVisit::okButton() {
    accept();
}
