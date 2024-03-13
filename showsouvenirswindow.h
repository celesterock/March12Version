#ifndef SHOWSOUVENIRSWINDOW_H
#define SHOWSOUVENIRSWINDOW_H

#include <QDialog>
#include "college.h"

namespace Ui {
    class ShowSouvenirsWindow;
}

class ShowSouvenirsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ShowSouvenirsWindow(const College &college, QWidget *parent = nullptr);
    ~ShowSouvenirsWindow();

private slots:


private:
    Ui::ShowSouvenirsWindow *ui;
};

#endif // SHOWSOUVENIRSWINDOW_H
