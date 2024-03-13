#include "collegelist.h"
#include "ui_collegelist.h"

CollegeList::CollegeList(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CollegeList)
{
    ui->setupUi(this);
}

CollegeList::~CollegeList()
{
    delete ui;
}

void CollegeList::populateListofColleges(const QVector<College>& colleges) {
    for(const College& college : colleges) {
        ui -> listWidget ->addItem(college.getCollegeName());
    }
}
