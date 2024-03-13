#include "college.h"


College::College() {}

College::College(QString name) : name(name) {}

College::~College(){}

void College::setName(QString name) {
    this -> name = name;
}

QString College::getCollegeName() const {
    return name;
}

void College::addSouvenir(Souvenir souvenirToAdd) {
    souvenirList.push_back(souvenirToAdd);
}

// void College::deleteSouvenir(string souvenirToDelete) {
//     int index = findSouvenirIndex(souvenirToDelete);
//     if(index != souvenirList.size()) {
//         souvenirList.erase(souvenirList.begin() + index);
//     }
//     else{
//         cout << "Souvenir does not exist/n/n";
//     }
// }


// void College::modifySouvenirPrice(string souvenirToModify, double newPrice) {
//     int index = findSouvenirIndex(souvenirToModify);
//     if(index != souvenirList.size()) {
//         souvenirList[index].modifyPrice(newPrice);
//     }
//     else{
//         cout << "Souvenir does not exist/n/n";
//     }
// }

// returns the index of the souvenir or souvenirList.size() if the sovenir is not in the vector
int College::findSouvenirIndex(const QString& souvenirName) {
    bool souvenirFound = false;
    int index = 0;
    while(!souvenirFound && index < souvenirList.size()) {
        if((souvenirList.at(index)).getName() == souvenirName) {
            souvenirFound = true;
        }
        else {
            index++;
        }
    }

    return index;
}

// returns the QVector of souvenirs for the college
QVector<Souvenir> College::getSouvenirOptions() const {
    return souvenirList;
}

ostream& operator << (ostream& out, const College& college) {
    out << "College Name: " << college.name.toStdString() << endl;
    out << "Souvenir List: \n";
    for (const Souvenir& souvenir : college.souvenirList) {
        out << souvenir;
    }

    out << endl << endl;

    return out;
}
