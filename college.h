#ifndef COLLEGE_H
#define COLLEGE_H


#include "souvenir.h"
#include <vector>
#include <iostream>
#include <string>
#include <QString>
#include <QDebug>
using namespace std;

class College {

public:
    College();
    College(QString name);
    ~College();

    QString getCollegeName()const;

    void setName(QString name);
    void addSouvenir(Souvenir souvenirToAdd);
    // void deleteSouvenir(string souvenirToDelete);
    // void modifySouvenirPrice(string souvenirToModify, double newPrice);
    QVector<Souvenir> getSouvenirOptions() const; // returns the QVector of souvenirs for the college


    friend ostream& operator << (ostream& out, const College& college);

private:
    QString name;
    QVector <Souvenir> souvenirList;
    int findSouvenirIndex(const QString& souvenirName);

};

#endif // COLLEGE_H
