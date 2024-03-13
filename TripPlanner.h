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

/**
 * @brief The TripPlanner class manages the planning and execution of college trips.
 */
class TripPlanner : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief This struct represents a node in the college purchases linked list.
     * It holds information about the college visited, including souvenir count and total cost.
     */
    struct CollegePurchasesNode {
        College college;                ///< College that is being visited
        int souvenirCount;              ///< Total number of souvenirs purchased at the college
        double totalCost;               ///< Total cost of items purchased at the college
        CollegePurchasesNode* next;     ///< Pointer to the next CollegePurchasesNode

        /**
         * @brief Constructs a CollegePurchasesNode object.
         * @param college The college being visited.
         */
        CollegePurchasesNode(const College& college) : college(college), souvenirCount(0), totalCost(0.0), next(nullptr) {}
    };

    /**
     * @brief Constructs a TripPlanner object.
     * @param dbManager Pointer to the DbManager instance.
     * @param parent Pointer to the parent widget.
     */
    explicit TripPlanner(DbManager* dbManager, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the TripPlanner object.
     */
    virtual ~TripPlanner();

    /**
     * @brief Adds a college to the trip.
     * @param collegeToAdd The college to add to the trip.
     */
    void addCollege(const College& collegeToAdd);

    /**
     * @brief Saves the purchases made at a college to the college purchases structure.
     * @param souvenirCount The total number of souvenirs purchased.
     * @param totalCost The total cost of souvenirs purchased.
     */
    void savePurchasesToCollegePurchasesStruct(int souvenirCount, double totalCost);

    /**
     * @brief Initiates a visit to a college campus.
     */
    void visitCampus();

    /**
     * @brief Prints a summary of purchases made during the trip.
     * This function is for testing only and can be deleted when the summary story is implemented.
     */
    void printPurchaseSummary();

private:
    DbManager* dbManager;                       ///< Pointer to DbManager instance
    CollegePurchasesNode* head;                 ///< Points to the front of the linked list
    CollegePurchasesNode* currentCollegeVisit;   ///< Points to the node of the current college
    Ui::TripPlanner *ui;                        ///< Pointer to the UI object

    /**
     * @brief Recursively determines the order of colleges to visit based on distance.
     * @param currentCollege The current college being visited.
     * @param remainingColleges Vector of remaining colleges to visit.
     * @param visitedColleges Vector of colleges already visited.
     */
    void recursivePlanTripOrder(const College& currentCollege, QVector<College>& remainingColleges, QVector<College>& visitedColleges);

    /**
     * @brief Calculates the distance between two colleges.
     * @param currentCollege The current college.
     * @param targetCollege The target college.
     * @param DistanceVec Vector containing distance data.
     * @return The distance between the two colleges.
     */
    double calculateDistance(const College& currentCollege, const College& targetCollege, const QVector<DistanceData>& DistanceVec);

    /**
     * @brief Plans the trip based on the list of colleges.
     * @param colleges Vector containing the list of colleges to visit.
     */
    void planTrip(QVector<College>& colleges);

    /**
     * @brief Prompts the user for the number of colleges to visit.
     * @return The number of colleges to visit.
     */
    int promptForNumberOfColleges();

    /**
     * @brief Plans the trip with a specified maximum number of colleges to visit.
     * @param colleges Vector containing the list of colleges to visit.
     * @param maxCollegesToVisit The maximum number of colleges to visit.
     */
    void planTrip(QVector<College>& colleges, int maxCollegesToVisit);

    /**
     * @brief Recursively determines the order of colleges to visit with a specified maximum number of colleges to visit.
     * @param currentCollege The current college being visited.
     * @param remainingColleges Vector of remaining colleges to visit.
     * @param visitedColleges Vector of colleges already visited.
     * @param maxCollegesToVisit The maximum number of colleges to visit.
     */
    void recursivePlanTripOrder(const College& currentCollege, QVector<College>& remainingColleges, QVector<College>& visitedColleges, int maxCollegesToVisit);

private slots:
    /**
     * @brief Slot function invoked when the "Begin Saddleback Trip" button is clicked.
     */
