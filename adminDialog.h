#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include "qdialog.h"
#include<vector>
#include "QLabel.h"
#include "QStackedWidget"
#include "QVBoxLayout"
#include "QLineEdit"
#include "QGridLayout"
#include "QPushButton"
#include "QMessageBox"
#include "QComboBox"
#include "college.h"
#include "dbmanager.h"



class adminDialog : public QDialog
{
    Q_OBJECT
public:
    adminDialog(DbManager* dbManager, QWidget* parent = nullptr);
    ~adminDialog();
    void setColleges();
private slots:
    void toOk();
    void toClear();
    void toModify();
    void toRemove();
    void toUpdate();
    void toExit();
    void getNames();
    void getName();

private:

    DbManager *manager;
    College college;
    QVector <College> Colleges;
    QStackedWidget* stackedWidget;
    QString realId = "Sprinters";
    QString realPassword = "12345";

    QPushButton* ok;
    QPushButton* clear;
    QPushButton* addCollege;
    QPushButton* custom;
    QPushButton* removeCollege;
    QPushButton* modifyCollege;
    QPushButton* update;
    QPushButton* exit;

    QLabel* userId;
    QLabel* passwordEntry;

    QLineEdit* id;
    QLineEdit* password;

    QAction* okAct;
    QAction* clearAct;


    void createButtons();
    void createActions();
    void createLoginScreen();
    void createMainPage();
    void toAdd(QString);
    void toCustom(const QString&);




};

#endif // ADMINDIALOG_H
