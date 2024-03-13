#ifndef INFOPAGEWINDOW_H
#define INFOPAGEWINDOW_H

#include <QDialog>

namespace Ui {
    class InfoPageWindow;
}

/**
 * @brief The InfoPageWindow class represents a dialog window to display information.
 */
class InfoPageWindow : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Explicit constructor for the InfoPageWindow class.
     * @param parent The parent widget (default is nullptr).
     */
    explicit InfoPageWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the InfoPageWindow class.
     */
    ~InfoPageWindow();

private:
    Ui::InfoPageWindow *ui; ///< Pointer to the UI object for the InfoPageWindow dialog window.
};

#endif // INFOPAGEWINDOW_H
