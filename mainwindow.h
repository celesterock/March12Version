#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "adminDialog.h"
#include <CollegeListWindow.h>
#include <visitcollegewindow.h>
#include <dbmanager.h>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class represents the main application window.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the MainWindow class.
     * @param dbManager Pointer to the DbManager instance.
     * @param parent The parent widget (default is nullptr).
     */
    explicit MainWindow(DbManager* dbManager, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the MainWindow class.
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui; ///< Pointer to the UI object for the MainWindow.

    DbManager* dbManager; ///< Pointer to the DbManager instance.

    CollegeList *collegeListWindow = nullptr; ///< Pointer to the college list window.

    adminDialog* newAdminDialog; ///< Pointer to the admin dialog window.

    QMenu* administrativeAccess; ///< Menu for administrative access.

    QAction* toLoginAct; ///< Action to switch to login view.

    /**
     * @brief Creates menus for the MainWindow.
     */
    void createMenus();

    /**
     * @brief Creates actions for the MainWindow.
     */
    void createActions();

    /**
     * @brief Creates the correct trip order for the trip planner.
     * @param trip Pointer to the TripPlanner instance.
     */
    void createCorrectTripOrder(TripPlanner* trip);

private slots:
    // void openCollegeListWindow();
    /**
     * @brief Slot to begin the trip.
     */
    void beginTrip();

    /**
     * @brief Slot to switch to login view.
     */
    void toLogin();
};

#endif // MAINWINDOW_H
