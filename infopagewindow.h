#ifndef INFOPAGEWINDOW_H
#define INFOPAGEWINDOW_H

#include <QDialog>

namespace Ui {
class InfoPageWindow;
}

class InfoPageWindow : public QDialog
{
    Q_OBJECT

public:
    explicit InfoPageWindow(QWidget *parent = nullptr);
    ~InfoPageWindow();

private:
    Ui::InfoPageWindow *ui;
};

#endif // INFOPAGEWINDOW_H
