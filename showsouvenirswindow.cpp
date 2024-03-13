#include "showsouvenirswindow.h"
#include "ui_showsouvenirswindow.h"


ShowSouvenirsWindow::ShowSouvenirsWindow(const College &college, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowSouvenirsWindow)
{
    ui->setupUi(this);

    // Set window title or any identifier to the selected college's name
    setWindowTitle(college.getCollegeName() + " Souvenirs");

    // Assuming College class has a method to get souvenirs which returns a list or vector of souvenirs
    for (const Souvenir &souvenir : college.getSouvenirOptions()) {
        QString itemText = QString("%1 - $%2").arg(souvenir.getName()).arg(souvenir.getPrice());
        ui->listWidget->addItem(itemText);
    }
}

ShowSouvenirsWindow::~ShowSouvenirsWindow() {
    delete ui;
}
