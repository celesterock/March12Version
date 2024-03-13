#include "VisitCampusScreen.h"
#include "ui_VisitCampusScreen.h"

InfoPageWindow::InfoPageWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoPageWindow)
{
    ui->setupUi(this);
}

InfoPageWindow::~InfoPageWindow()
{
    delete ui;
}
