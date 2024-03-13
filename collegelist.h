#ifndef COLLEGELIST_H
#define COLLEGELIST_H

#include <QDialog>
#include <dbmanager.h>

namespace Ui {
class CollegeList;
}

class CollegeList : public QDialog
{
    Q_OBJECT

public:
    explicit CollegeList(QWidget *parent = nullptr);
    ~CollegeList();
    void populateListofColleges(const QVector<College>& colleges);

private:
    Ui::CollegeList *ui;
};

#endif // COLLEGELIST_H
