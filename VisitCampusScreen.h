#ifndef VISITCAMPUSSCREEN_H
#define VISITCAMPUSSCREEN_H

#include <QDialog>

namespace Ui {
class InfoPageWindow;
}

/**
 * @brief The InfoPageWindow class represents a dialog for displaying information about visiting a college campus.
 */
class InfoPageWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs an InfoPageWindow object.
     * @param parent Pointer to the parent widget.
     */
    explicit InfoPageWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the InfoPageWindow object.
     */
    ~InfoPageWindow();

private:
    Ui::InfoPageWindow *ui; ///< Pointer to the UI object
};

#endif // VISITCAMPUSSCREEN_H
