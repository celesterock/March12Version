QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../tripSummary.cpp \
    CollegeListWindow.cpp \
    TripPlanner.cpp \
    adminDialog.cpp \
    college.cpp \
    customtrip.cpp \
    dbmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    numofcollegestovisit.cpp \
    showcollegeswindow.cpp \
    showsouvenirswindow.cpp \
    souvenir.cpp \
    visitcollegewindow.cpp

HEADERS += \
    ../tripSummary.h \
    CollegeListWindow.h \
    TripPlanner.h \
    adminDialog.h \
    college.h \
    customtrip.h \
    dbmanager.h \
    mainwindow.h \
    numofcollegestovisit.h \
    showcollegeswindow.h \
    showsouvenirswindow.h \
    souvenir.h \
    visitcollegewindow.h

FORMS += \
    ../tripSummary.ui \
    CollegeListWindow.ui \
    mainwindow.ui \
    numofcollegestovisit.ui \
    showcollegeswindow.ui \
    showsouvenirswindow.ui \
    tripplanner.ui \
    visitcollegewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
