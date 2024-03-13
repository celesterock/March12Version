#ifndef COLLEGELISTWINDOW_H
#define COLLEGELISTWINDOW_H

#include <QDialog>
#include <dbmanager.h>

namespace Ui {
class CollegeList;
}

class CollegeList : public QDialog
{
    Q_OBJECT

public:
    explicit CollegeList(DbManager* dbManager, QWidget *parent = nullptr);
    ~CollegeList();
    void populateListofColleges();
    QVector<College> getSelectedColleges();
    College getStartingCollege();

private slots:
    void BeginTripClicked();

private:
    Ui::CollegeList *ui;
    DbManager *dbManager; // pointer to DbManager instance
    College findCollegeByName(const QString& name);
    College startingCollege;
};

#endif // COLLEGELISTWINDOW_H
