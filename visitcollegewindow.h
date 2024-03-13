#ifndef VISITCOLLEGEWINDOW_H
#define VISITCOLLEGEWINDOW_H

#include <QDialog>
#include "college.h"
#include "tripplanner.h"

namespace Ui {
class VisitCollegeWindow;
}

/**
 * @brief The VisitCollegeWindow class represents the window for visiting a college.
 */
class VisitCollegeWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the VisitCollegeWindow class.
     * @param trip Pointer to the TripPlanner instance.
     * @param parent The parent widget.
     */
    explicit VisitCollegeWindow(TripPlanner* trip, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the VisitCollegeWindow class.
     */
    ~VisitCollegeWindow();

    /**
     * @brief Sets the college to be visited.
     * @param collegeToVisit The college to be visited.
     */
    void setCollege(const College& collegeToVisit);

    /**
     * @brief Populates the souvenir table with souvenirs and prices.
     * @param collegeToVisit The college to visit.
     */
    void populateSouvenirTable(const College& collegeToVisit);

private:
    Ui::VisitCollegeWindow *ui;
    TripPlanner* trip;

private slots:
    /**
     * @brief Slot to handle the purchase button click event.
     */
    void purchaseButtonClick();

};

#endif // VISITCOLLEGEWINDOW_H
