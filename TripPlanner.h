#ifndef TRIPPLANNER_H
#define TRIPPLANNER_H

#include "college.h"
#include "dbmanager.h"
#include "CollegeListWindow.h"

#include <QQueue>
#include <QDialog>
#include <QDebug>

namespace Ui {
class TripPlanner;
}

// forward declaration
class VisitCollegeWindow;

class TripPlanner : public QDialog
{
    Q_OBJECT

public:
    /* This struct will be created for each college in the student's trip
     * It holds the total number of souvenirs purchased at the college
     *   and the total cost of souvenirs purchased at the college */
    struct CollegePurchasesNode {
        College college;        // College that is being visited
        int souvenirCount;      // total number of souvenirs purchases at the college
        double totalCost;                 // total cost of items purchased at the college
        CollegePurchasesNode* next = nullptr; // pointer to next CollegePurchasesNode Node

        /* Allows for the addition of a college to the tripPurchases vector before the
           souvenirs have been purchases */
        CollegePurchasesNode(const College& college) : college(college), souvenirCount(0), totalCost(0.0), next(nullptr) {}
    };

    explicit TripPlanner(DbManager* dbManager, QWidget *parent = nullptr);
    virtual ~TripPlanner();
    void addCollege(const College& collegeToAdd);
    void savePurchasesToCollegePurchasesStruct(int souvenirCount,
                                               double totalCost);
    void visitCampus();

    // this function is for testing only, can be deleted when the summary story is impelmented
    void printPurchaseSummary();

private:
    DbManager* dbManager; // pointer to DbManager instance
    CollegePurchasesNode* head; // Points to the front of the linked list
    CollegePurchasesNode* currentCollegeVisit; // points to the node of the current college
    Ui::TripPlanner *ui;

    // Recusrively Function: determines which college to visit next based on distance
    void recursivePlanTripOrder(const College& currentCollege,
                                QVector<College>& remainingColleges,
                                QVector<College>& visitedColleges);
    double calculateDistance(const College& currentCollege, const College& targetCollege, const QVector<DistanceData>& DistanceVec);

    void planTrip(QVector<College>& colleges);
    int promptForNumberOfColleges();
    void planTrip(QVector<College>& colleges, int maxCollegesToVisit);
    void recursivePlanTripOrder(const College& currentCollege,
                                QVector<College>& remainingColleges,
                                QVector<College>& visitedColleges,
                                int maxCollegesToVisit);

private slots:
    void BeginSaddlebackTrip();
    void BeginASUTrip();
    void BeginUCITrip();
    void BeginCustomTrip();

};

#endif // TRIPPLANNER_H
