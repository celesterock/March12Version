#include "infopagewindow.h"
#include "ui_infopagewindow.h"

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
