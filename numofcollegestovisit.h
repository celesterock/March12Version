#ifndef NUMOFCOLLEGESTOVISIT_H
#define NUMOFCOLLEGESTOVISIT_H

#include <QDialog>
#include "dbmanager.h"

namespace Ui {
    class NumOfCollegesToVisit;
}

/**
 * @brief The NumOfCollegesToVisit class represents a dialog for selecting the number of colleges to visit.
 */
class NumOfCollegesToVisit : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the NumOfCollegesToVisit class.
     * @param dbManager Pointer to the DbManager instance.
     * @param parent The parent widget (default is nullptr).
     */
    NumOfCollegesToVisit(DbManager* dbManager, QWidget *parent);

    /**
     * @brief Destructor for the NumOfCollegesToVisit class.
     */
    ~NumOfCollegesToVisit();

    /**
     * @brief Gets the number of colleges selected by the user.
     * @return The number of colleges to visit.
     */
    int getNumberOfColleges() const;

private slots:
    /**
     * @brief Slot called when the OK button is clicked.
     */
    void okButton();

private:
    Ui::NumOfCollegesToVisit *ui; ///< Pointer to the UI object for the NumOfCollegesToVisit dialog.

    DbManager* dbManager; ///< Pointer to the DbManager instance.
};

#endif // NUMOFCOLLEGESTOVISIT_H
