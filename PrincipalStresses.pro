QT       += core gui openglwidgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    mohrcircleplot.cpp \
    qcustomplot.cpp \
    stresscalculator.cpp

HEADERS += \
    glwidget.h \
    mainwindow.h \
    mohrcircleplot.h \
    qcustomplot.h \
    stresscalculator.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    PrincipalStresses_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Custom
INCLUDEPATH += /usr/include/eigen3
