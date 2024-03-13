QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CollegeListWindow.cpp \
    TripPlanner.cpp \
    adminDialog.cpp \
    college.cpp \
    customtrip.cpp \
    dbmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    numofcollegestovisit.cpp \
    showsouvenirswindow.cpp \
    souvenir.cpp \
    visitcollegewindow.cpp

HEADERS += \
    CollegeListWindow.h \
    TripPlanner.h \
    adminDialog.h \
    college.h \
    customtrip.h \
    dbmanager.h \
    mainwindow.h \
    numofcollegestovisit.h \
    showsouvenirswindow.h \
    souvenir.h \
    visitcollegewindow.h

FORMS += \
    CollegeListWindow.ui \
    mainwindow.ui \
    numofcollegestovisit.ui \
    showsouvenirswindow.ui \
    tripplanner.ui \
    visitcollegewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
