#include "TripPlanner.h"
#include "ui_tripplanner.h"
#include "visitcollegewindow.h" // full class definition (DO NOT REMOVE)
#include "numofcollegestovisit.h"

TripPlanner::TripPlanner(DbManager* dbManager, QWidget *parent)
    :  QDialog(parent), dbManager(dbManager), ui(new Ui::TripPlanner)
{
    ui->setupUi(this);
    // Connect the button's clicked signal to the BeginSaddlebackTrip() slot
    connect(ui->BeginSaddlebackTrip, &QPushButton::clicked, this, &TripPlanner::BeginSaddlebackTrip);
    // Connect the button's clicked signal to the BeginASUTrip() slot
    connect(ui->BeginASUTrip, &QPushButton::clicked, this, &TripPlanner::BeginASUTrip);
    // Connect the button's clicked signal to the BeginUCITrip() slot
    connect(ui->BeginUCITrip, &QPushButton::clicked, this, &TripPlanner::BeginUCITrip);
    // Connect the button's clicked signal to the BeginCustomTrip() slot
    connect(ui->BeginCustomTrip, &QPushButton::clicked, this, &TripPlanner::BeginCustomTrip);
}


// deallocate memory
TripPlanner::~TripPlanner()
{
    while(head != nullptr) {
        CollegePurchasesNode* temp = head;
        head = head -> next;
        delete temp;
    }
    delete ui;
}



/***************************************************************************
 * Adds a College object to the trip's linked list via creating a
 *    "College Purchases" node, filling in the college object, and setting
 *    the purchases/total to zero.
***************************************************************************/
void TripPlanner::addCollege(const College& collegeToAdd) {
    // CASE 1: the list is empty
    if(head == nullptr) {
        head = new CollegePurchasesNode(collegeToAdd);
        // the currentCollegeVisit pointer will point to the same node as head
        currentCollegeVisit = head;
    }
    // CASE 2: the list already contains colleges
    else {
        CollegePurchasesNode* temp = head;
        // traverse the list to find the end where the new college will be added
        while(temp->next != nullptr) {
            temp = temp -> next;
        }
        temp -> next = new CollegePurchasesNode(collegeToAdd);
    }
}

/* *************************************************************************
 * This function is called in VisitCollegeWindow.cpp.
 * Purpose: The souvenir count and total cost is being calculated directly
 * from the UI table information. However, we need a way to store this information
 * for summary purposes. Thus, this method is called once the student
 * has selected to confirm the purchases, and it updates the vector of
 * CollegePurchasesNode structs to store the purchase info.
 * *************************************************************************/
void TripPlanner::savePurchasesToCollegePurchasesStruct(int souvenirCount,
                                                 double totalCost) {
    // update the Node
    currentCollegeVisit->souvenirCount += souvenirCount;
    currentCollegeVisit->totalCost += totalCost;
}

/* *************************************************************************
 * Method is for testing only. Can be deleted when summary page is implemented.
 * *************************************************************************/
void TripPlanner::printPurchaseSummary() {
    qDebug() << "Total Items Purchased: " << currentCollegeVisit->souvenirCount;
    qDebug() << "Total Cost: " << currentCollegeVisit->totalCost;

}

/* *************************************************************************
 * Creates the purchasing page for each college. Once a purchase has
 *  been completed, the next college page will automatically pop up until
 *  there are no more colleges left in the trip.
 * *************************************************************************/
void TripPlanner::visitCampus() {
    while(currentCollegeVisit != nullptr) {

        VisitCollegeWindow* collegeWindow = new VisitCollegeWindow(this);

        // sets the college name at the top of the window
        collegeWindow->setCollege(currentCollegeVisit -> college);

        collegeWindow->exec();

        // move on to the next college
        currentCollegeVisit = currentCollegeVisit -> next;
    }

}

void TripPlanner::recursivePlanTripOrder(const College& currentCollege,
                            QVector<College>& remainingColleges,
                            QVector<College>& visitedColleges) {
    if(remainingColleges.isEmpty()) {
        return;
    }

    double minDistance = std::numeric_limits<double>::max();
    int indexOfNextCollege = -1;

    // Find the college in 'remainingColleges' that is closest to 'currentCollege'
    for (int i = 0; i < remainingColleges.size(); ++i) {
        double distance = calculateDistance(currentCollege, remainingColleges[i], dbManager->DistanceVec);
        if (distance < minDistance) {
            minDistance = distance;
            indexOfNextCollege = i;
        }
    }

    // The next college to visit based on the shortest distance
    College nextCollege = remainingColleges[indexOfNextCollege];

    qDebug() << "Closest College is: " << nextCollege.getCollegeName();


    // Add 'nextCollege' to the list of visited colleges
    visitedColleges.push_back(nextCollege);

    // Remove 'nextCollege' from the list of remaining colleges
    remainingColleges.remove(indexOfNextCollege);

    // Recursive call with the new current college and the updated list of remaining colleges
    recursivePlanTripOrder(nextCollege, remainingColleges, visitedColleges);
}

double TripPlanner::calculateDistance(const College& currentCollege, const College& targetCollege, const QVector<DistanceData>& DistanceVec) {
    QString currentCollegeName = currentCollege.getCollegeName();
    QString targetCollegeName = targetCollege.getCollegeName();

    for (const DistanceData& data : DistanceVec) {
        if ((data.startCollege == currentCollegeName && data.endCollege == targetCollegeName) ||
            (data.startCollege == targetCollegeName && data.endCollege == currentCollegeName)) {

            qDebug() << "Distance between: ";
            qDebug() << currentCollegeName;
            qDebug() << " and ";
            qDebug() << targetCollegeName;
                qDebug() << " is " << data.distance;
            // Found the matching distance entry, return the distance
            return data.distance;
        }
    }

    // If no matching entry is found, return a large number to indicate no direct path or an error
    return std::numeric_limits<double>::max();
};


void TripPlanner::planTrip(QVector<College>& colleges) {
    if (colleges.isEmpty()) {
        return;
    }

    QVector<College> visitedColleges;
    College startingCollege = colleges.first();
    qDebug() << "Starting College is: ";
    qDebug() << startingCollege.getCollegeName();

    // Remove the starting college from the list of remaining colleges
    QVector<College> remainingColleges = colleges;
    remainingColleges.removeFirst();

    // Start the recursion with the starting college
    recursivePlanTripOrder(startingCollege, remainingColleges, visitedColleges);

    visitedColleges.push_front(startingCollege);

    for(const College& college : visitedColleges) {
        addCollege(college);
    }

}


void TripPlanner::BeginSaddlebackTrip() {

    // Assume 'CollegeVec' is the original vector of College objects
    QVector<College> CollegeVec = dbManager->getCollegeVec();

    // Copy 'CollegeVec' into a new vector
    QVector<College> newCollegeVec = CollegeVec;

    // The name prefix to search for
    QString namePrefix = "Saddleback";

    // Ensure we're using a non-const iterator from the beginning
    auto it = std::find_if(newCollegeVec.begin(), newCollegeVec.end(), [&namePrefix](const College& college) {
        return college.getCollegeName().startsWith(namePrefix);
    });


    if (it != newCollegeVec.end()) {
        College foundCollege = *it;  // Here we're dereferencing a non-const iterator, which is fine
        newCollegeVec.erase(it);  // Using a non-const iterator in erase() is also fine
        newCollegeVec.prepend(foundCollege);
    }


    planTrip(newCollegeVec);

    visitCampus();
}

  void TripPlanner::BeginASUTrip() {
      // Assume 'CollegeVec' is the original vector of College objects
      QVector<College> CollegeVec = dbManager->getCollegeVec();

      // Copy 'CollegeVec' into a new vector
      QVector<College> newCollegeVec = CollegeVec;

      // The name prefix to search for
      QString namePrefix = "Arizona State University";

      // Ensure we're using a non-const iterator from the beginning
      auto it = std::find_if(newCollegeVec.begin(), newCollegeVec.end(), [&namePrefix](const College& college) {
          return college.getCollegeName().startsWith(namePrefix);
      });

      if (it != newCollegeVec.end()) {
          College foundCollege = *it;  // Here we're dereferencing a non-const iterator, which is fine
          newCollegeVec.erase(it);  // Using a non-const iterator in erase() is also fine
          newCollegeVec.prepend(foundCollege);
      }

      int collegeCount = promptForNumberOfColleges();

      planTrip(newCollegeVec, collegeCount);

      visitCampus();
 }

  void TripPlanner::planTrip(QVector<College>& colleges, int maxCollegesToVisit) {
      if (colleges.isEmpty() || maxCollegesToVisit <= 0) {
          return;
      }

      QVector<College> visitedColleges;
      College startingCollege = colleges.first();
      QVector<College> remainingColleges = colleges;
      remainingColleges.removeFirst();

      // Adjust recursivePlanTripOrder to consider the limit of maxCollegesToVisit
      recursivePlanTripOrder(startingCollege, remainingColleges, visitedColleges, maxCollegesToVisit);

      // Only add up to maxCollegesToVisit colleges to the trip
      for (int i = 0; i < visitedColleges.size() && i < maxCollegesToVisit; ++i) {
          addCollege(visitedColleges[i]);
      }
  }

  void TripPlanner::recursivePlanTripOrder(const College& currentCollege,
                                           QVector<College>& remainingColleges,
                                           QVector<College>& visitedColleges,
                                           int maxCollegesToVisit) {
      if (remainingColleges.isEmpty() || visitedColleges.size() >= maxCollegesToVisit) {
          return;
      }

      double minDistance = std::numeric_limits<double>::max();
      int indexOfNextCollege = -1;

      for (int i = 0; i < remainingColleges.size(); ++i) {
          double distance = calculateDistance(currentCollege, remainingColleges[i], dbManager->DistanceVec);
          if (distance < minDistance) {
              minDistance = distance;
              indexOfNextCollege = i;
          }
      }

      if (indexOfNextCollege != -1) {
          College nextCollege = remainingColleges[indexOfNextCollege];
          visitedColleges.push_back(nextCollege);
          remainingColleges.remove(indexOfNextCollege);
          recursivePlanTripOrder(nextCollege, remainingColleges, visitedColleges, maxCollegesToVisit);
      }
  }

  int TripPlanner::promptForNumberOfColleges()
  {
      NumOfCollegesToVisit dialog(dbManager, this);
      if(dialog.exec() == QDialog::Accepted)
      {
          int numberOfColleges = dialog.getNumberOfColleges();
          return numberOfColleges;
      }
      else {
          return -1;
      }
  }

  void TripPlanner::BeginUCITrip() {
      // Assume 'CollegeVec' is the original vector of College objects
      QVector<College> CollegeVec = dbManager->getCollegeVec();

      // Copy 'CollegeVec' into a new vector
      QVector<College> newCollegeVec = CollegeVec;

      // The name prefix to search for
      QString namePrefix = "University of California, Irvine (UCI)";

      // Ensure we're using a non-const iterator from the beginning
      auto it = std::find_if(newCollegeVec.begin(), newCollegeVec.end(), [&namePrefix](const College& college) {
          return college.getCollegeName().startsWith(namePrefix);
      });


      if (it != newCollegeVec.end()) {
          College foundCollege = *it;  // Here we're dereferencing a non-const iterator, which is fine
          newCollegeVec.erase(it);  // Using a non-const iterator in erase() is also fine
          newCollegeVec.prepend(foundCollege);
      }


      planTrip(newCollegeVec);

      visitCampus();
  }

  void TripPlanner::BeginCustomTrip() {
      CollegeList dialog(dbManager, this);

      if (dialog.exec() == QDialog::Accepted) { // The dialog is displayed modally and waits for user interaction
          QVector<College> selectedColleges = dialog.getSelectedColleges(); // Retrieve the selected colleges after the dialog is closed
          // The name prefix to search for
          QString namePrefix = dialog.getStartingCollege().getCollegeName();

          // Ensure we're using a non-const iterator from the beginning
          auto it = std::find_if(selectedColleges.begin(), selectedColleges.end(), [&namePrefix](const College& college) {
              return college.getCollegeName().startsWith(namePrefix);
          });


          if (it != selectedColleges.end()) {
              College foundCollege = *it;  // Here we're dereferencing a non-const iterator, which is fine
              selectedColleges.erase(it);  // Using a non-const iterator in erase() is also fine
              selectedColleges.prepend(foundCollege);
          }


          planTrip(selectedColleges);

          visitCampus();
      }
  }


