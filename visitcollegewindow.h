#ifndef VISITCOLLEGEWINDOW_H
#define VISITCOLLEGEWINDOW_H

#include <QDialog>
#include "college.h"
#include "tripplanner.h"

namespace Ui {
class VisitCollegeWindow;
}

class VisitCollegeWindow : public QDialog
{
    Q_OBJECT

public:
    /* points to the Trip instance so that it can update the souvenirs
     * purchased / total cost for each college that has been visited */
    explicit VisitCollegeWindow(TripPlanner* trip, QWidget *parent = nullptr);
    ~VisitCollegeWindow();

    // Sets the college name that will be visited
    void setCollege(const College& collegeToVisit);

    // Puts the souvenirs & prices into the table
    void populateSouvenirTable(const College& collegeToVisit);


private:
    Ui::VisitCollegeWindow *ui;
    TripPlanner* trip;

private slots:
    void purchaseButtonClick();

};

#endif // VISITCOLLEGEWINDOW_H
