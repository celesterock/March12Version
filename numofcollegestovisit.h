#ifndef NUMOFCOLLEGESTOVISIT_H
#define NUMOFCOLLEGESTOVISIT_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
class NumOfCollegesToVisit;
}

class NumOfCollegesToVisit : public QDialog
{
    Q_OBJECT

public:
    NumOfCollegesToVisit(DbManager* dbManager, QWidget *parent);
    ~NumOfCollegesToVisit();
    int getNumberOfColleges() const;

private slots:
    void okButton();

private:
    Ui::NumOfCollegesToVisit *ui;
    DbManager* dbManager; // pointer to DbManager instance
};

#endif // NUMOFCOLLEGESTOVISIT_H
