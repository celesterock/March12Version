#ifndef COLLEGELISTWINDOW_H
#define COLLEGELISTWINDOW_H

#include <QDialog>
#include <dbmanager.h>

/**
 * @brief The CollegeList class provides a dialog window to display a list of colleges.
 */
namespace Ui {
class CollegeList;
}

class CollegeList : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a CollegeList object.
     * @param dbManager Pointer to the DbManager instance.
     * @param parent Pointer to the parent widget.
     */
    explicit CollegeList(DbManager* dbManager, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the CollegeList object.
     */
    ~CollegeList();

    /**
     * @brief Populates the list of colleges in the UI.
     */
    void populateListofColleges();

    /**
     * @brief Retrieves the list of selected colleges from the UI.
     * @return A QVector containing the selected colleges.
     */
    QVector<College> getSelectedColleges();

    /**
     * @brief Retrieves the starting college for the trip.
     * @return The starting college for the trip.
     */
    College getStartingCollege();

private slots:
    /**
     * @brief Slot function invoked when the "Begin Trip" button is clicked.
     */
    void BeginTripClicked();

private:
    Ui::CollegeList *ui; ///< Pointer to the UI object.
    DbManager *dbManager; ///< Pointer to the DbManager instance.
    
    /**
     * @brief Finds a college by its name.
     * @param name The name of the college to find.
     * @return The College object with the specified name.
     */
    College findCollegeByName(const QString& name);

    College startingCollege; ///< The starting college for the trip.
};

#endif // COLLEGELISTWINDOW_H
