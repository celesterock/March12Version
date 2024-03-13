#ifndef COLLEGELIST_H
#define COLLEGELIST_H

#include <QDialog>
#include <dbmanager.h>

namespace Ui {
    class CollegeList;
}

/**
 * @brief The CollegeList class represents a dialog window to display a list of colleges.
 */
class CollegeList : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Explicit constructor for the CollegeList class.
     * @param parent The parent widget (default is nullptr).
     */
    explicit CollegeList(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the CollegeList class.
     */
    ~CollegeList();

    /**
     * @brief Function to populate the list of colleges in the dialog window.
     * @param colleges A QVector of College objects representing the colleges to be displayed.
     */
    void populateListofColleges(const QVector<College>& colleges);

private:
    Ui::CollegeList *ui; ///< Pointer to the UI object for the CollegeList dialog window.
};

#endif // COLLEGELIST_H
