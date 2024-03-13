#ifndef SHOWCOLLEGESWINDOW_H
#define SHOWCOLLEGESWINDOW_H

#include <QDialog>
#include "dbmanager.h"
namespace Ui {
class showcollegeswindow;
}

class showcollegeswindow : public QDialog
{
    Q_OBJECT

public:
    explicit showcollegeswindow(DbManager *dbManager, QWidget *parent = nullptr);
    ~showcollegeswindow();


private slots:
    void on_collegeSelected();

private:
    Ui::showcollegeswindow *ui;
    DbManager *dbManager;
    void populateCollegeDistanceTable();
};

#endif // SHOWCOLLEGESWINDOW_H
