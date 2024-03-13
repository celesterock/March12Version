#include "adminDialog.h"
#include "QInputDialog"

adminDialog::adminDialog(DbManager* dbManager, QWidget* parent) : QDialog(parent), manager(dbManager)
{

    stackedWidget = new QStackedWidget(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    createButtons();
    createLoginScreen();
}
adminDialog::~adminDialog()
{

}
void adminDialog::createActions()
{
    connect(ok, &QPushButton::clicked, this, &adminDialog::toOk);
    connect(clear, &QPushButton::clicked, this, &adminDialog::toClear);
    connect(addCollege, &QPushButton::clicked, this, &adminDialog::getNames);
    connect(modifyCollege, &QPushButton::clicked, this, &adminDialog::toModify);
    connect(removeCollege, &QPushButton::clicked, this, &adminDialog::toRemove);
    connect(update, &QPushButton::clicked, this, &adminDialog::toUpdate);
    connect(exit, &QPushButton::clicked, this, &adminDialog::toExit);
    connect(custom, &QPushButton::clicked, this, &adminDialog::getName);
    //connect(addCollege, &QPushButton::clicked, this, &adminDialog::toAddCollege);
}

void adminDialog::createButtons()
{
    update = new QPushButton("Update");
    exit = new QPushButton("Exit");
}

void adminDialog::createLoginScreen()
{
    ok = new QPushButton("Ok");
    clear = new QPushButton("Clear");
    userId = new QLabel("User ID: ");
    passwordEntry = new QLabel("Password: ");

    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);
    id = new QLineEdit;

    QGridLayout* loginScreenLayout = new QGridLayout;
    loginScreenLayout->addWidget(ok, 2, 0, Qt::AlignBottom);
    loginScreenLayout->addWidget(clear, 2, 2, Qt::AlignBottom);
    loginScreenLayout->addWidget(userId, 0, 0, Qt::AlignTop | Qt::AlignLeft);
    loginScreenLayout->addWidget(passwordEntry, 1, 0, Qt::AlignTop | Qt::AlignLeft);
    loginScreenLayout->addWidget(id, 0, 1, Qt::AlignTop | Qt::AlignRight);
    loginScreenLayout->addWidget(password, 1, 1, Qt::AlignTop | Qt::AlignRight);

    QWidget* page1 = new QWidget;
    stackedWidget->addWidget(page1);
    page1->setFixedSize(250, 200);
    page1->setLayout(loginScreenLayout);
    createActions();


}
void adminDialog::createMainPage()
{
    /*auto it = find_if(colleges.begin(), colleges.end(),
                      [&_name_](const std::unique_ptr<Colleges>& obj) {return obj->getIdName() == _name_;});*/
    addCollege = new QPushButton("Add");
    removeCollege = new QPushButton("remove");
    modifyCollege = new QPushButton("Edit");
    custom = new QPushButton("Custom");
    qDebug() << "Create Main Page";
    QStringList names;
    names << "College1" << "College2" << "College3";
    QComboBox* collegeNames = new QComboBox(this);
    collegeNames->addItems(names);
    QLabel* colleges = new QLabel("Colleges");
    colleges->setBuddy(collegeNames);


    QGridLayout* mainPageLayout = new QGridLayout;
    mainPageLayout->addWidget(collegeNames, 0, 0, Qt::AlignTop | Qt::AlignLeft);
    mainPageLayout->addWidget(addCollege, 0, 1, Qt::AlignTop | Qt::AlignRight);
    mainPageLayout->addWidget(removeCollege, 0, 2, Qt::AlignTop | Qt::AlignRight);
    mainPageLayout->addWidget(modifyCollege, 0, 3, Qt::AlignTop | Qt::AlignRight);
    mainPageLayout->addWidget(custom, 0, 4, Qt::AlignTop | Qt::AlignRight);


    QWidget* page2 = new QWidget;
    stackedWidget->addWidget(page2);
    page2->setLayout(mainPageLayout);
    stackedWidget->setCurrentIndex(1);
    createActions();
}

void adminDialog::getNames()
{
    bool ok;
    QString name;
    QStringList names;
    const QVector<College>& availableColleges = manager->getAvailableColleges();
    for(College aCollege : availableColleges)
    {
        name = college.getCollegeName();

        if(!names.contains(name))
        {
            names.append(name);
        }

    }
    QString chosen = QInputDialog::getItem(this,"Select College ", "College: ", names, 0, false, &ok);
    if (&ok && !chosen.isEmpty())
    {
        toAdd(chosen);
    }
    else
    {
        QMessageBox* errorBox = new QMessageBox(QMessageBox::Warning, "Error", "List is empty", QMessageBox::Ok);
        errorBox->exec();

    }

}
void adminDialog::getName()
{
    bool ok;

    QString chosen = QInputDialog::getText(this,"Select College ", "College: ", QLineEdit::Normal, "", &ok);
    if (&ok && !chosen.isEmpty())
    {
        toCustom(chosen);
    }

}
void adminDialog::toOk()
{
    QMessageBox* errorMessage = new QMessageBox;
    if (password->text() == realPassword && id->text() == realId)
    {
        createMainPage();
    }
    else
    {
        errorMessage->setText("Incorrect: Please try again");
        errorMessage->show();
        toClear();
    }
}
void adminDialog::toClear()
{
    this->id->setText("");
    this->password->setText("");
}
void adminDialog::toAdd(QString chosen)
{
    qDebug() << "To add";
    QVBoxLayout* addLayout = new QVBoxLayout;
    update = new QPushButton("Update");
    college.setName(chosen);
    QString nameLabel2 = college.getCollegeName();
    addLayout->addWidget(new QLabel(nameLabel2, this));
    QVector<Souvenir> souvenirs;  // Create a vector to store Souvenir instances

    for (int i = 0; i < 7; i++)
    {
        QLineEdit* souvenirName = new QLineEdit(this);
        souvenirName->setAlignment(Qt::AlignLeft);
        souvenirName->setFixedHeight(30);
        souvenirName->setFixedWidth(200);

        QLineEdit* souvenirCost = new QLineEdit(this);
        souvenirCost->setAlignment(Qt::AlignRight);
        souvenirCost->setFixedHeight(30);
        souvenirCost->setFixedWidth(200);

        QString nameLabel = "Name: " + QString::number(i + 1);

        addLayout->addWidget(new QLabel(nameLabel, this));
        addLayout->addWidget(souvenirName);
        addLayout->addWidget(souvenirCost);
        if (souvenirName && souvenirCost)
        {
            Souvenir souvenir(souvenirName->text(), souvenirCost->text().toDouble());
            souvenirs.append(souvenir);
        }
    }


    // Now you have a vector (souvenirs) containing seven instances of Souvenir
    // You can add these to the college vector as needed
    for (const Souvenir& souvenir : souvenirs)
    {
        college.addSouvenir(souvenir);
    }

    addLayout->addWidget(update, Qt::AlignBottom, Qt::AlignLeft);
    addLayout->addWidget(exit, Qt::AlignBottom, Qt::AlignRight);

    QWidget* page3 = new QWidget;
    stackedWidget->addWidget(page3);
    page3->setLayout(addLayout);
    stackedWidget->setCurrentIndex(2);
    createActions();
}

void adminDialog::toModify()
{
    QVBoxLayout* modifyLayout = new QVBoxLayout;
    update = new QPushButton("Update");
    QVector<Souvenir> souvenirs;
    for (const College& c : manager->getCollegeVec())
    {
        Colleges.append(c);
        souvenirs.append(c.getSouvenirOptions());
    }

    for (int i = 0; i < 7; i++)
    {
        QLineEdit* souvenirName = new QLineEdit(this);
        souvenirName->setText(souvenirs[i].getName());
        souvenirName->setAlignment(Qt::AlignLeft);
        souvenirName->setFixedHeight(30);
        souvenirName->setFixedWidth(200);

        QLineEdit* souvenirCost = new QLineEdit(this);
        souvenirCost->setText(QString::number((souvenirs[i].getPrice())));
        souvenirCost->setAlignment(Qt::AlignRight);
        souvenirCost->setFixedHeight(30);
        souvenirCost->setFixedWidth(200);

        QString nameLabel = "Name: " + QString::number(i + 1);

        modifyLayout->addWidget(new QLabel(nameLabel, this));
        modifyLayout->addWidget(souvenirName);
        modifyLayout->addWidget(souvenirCost);
    }
    createActions();

}
void adminDialog::toRemove()
{
    bool ok;
    QString name;
    QStringList names;
    for(College c : manager->getCollegeVec())
    {
        name = c.getCollegeName();
        names.append(name);
    }
    QString chosen = QInputDialog::getItem(this,"Select College ", "College: ", names, 0, false, &ok);
    if (&ok && !chosen.isEmpty())
    {
        // manager->deleteCollege(name);
    }
    else
    {
        QMessageBox* errorBox = new QMessageBox(QMessageBox::Warning, "Error", "List is empty", QMessageBox::Ok);
        errorBox->exec();

    }
    createActions();
}
void adminDialog::toUpdate()
{
    // manager->addColleges(college.getCollegeName());
    manager->addSouvenirs(college);
}
void adminDialog::toExit()
{
    stackedWidget->setCurrentIndex(1);
}
void adminDialog::toCustom(const QString& chosen)
{
    bool ok;
    double dis;
    bool allGood = true;

    QStringList existingColleges;

    for(const College& c : manager->getCollegeVec())
    {
        existingColleges.append(c.getCollegeName());
    }
    for (const QString& name : existingColleges)
    {
        QString input = QInputDialog::getText(this, "Enter Distance", "Distance from " + chosen + " to " + name + ":", QLineEdit::Normal, " ", &ok);

        if (&ok && !input.isEmpty())
        {
            dis = input.toDouble();
            // manager->addDistances(chosen, name, dis);
        }
        else
        {
            // manager->deleteDistances(chosen);
            allGood = false;
            break;
        }
    }

    if (allGood)
    {
        toAdd(chosen);
    }

}
