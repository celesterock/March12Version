#ifndef VISITCAMPUSSCREEN_H
#define VISITCAMPUSSCREEN_H

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

#endif // VISITCAMPUSSCREEN_H
