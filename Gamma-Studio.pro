QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    etiquetas.cpp \
    funcioneswidget.cpp \
    graficas.cpp \
    importar.cpp \
    latex.cpp \
    main.cpp \
    mainwindow.cpp \
    matriceswidget.cpp \
    nuevoproyecto.cpp


HEADERS += \
    etiquetas.h \
    funcioneswidget.h \
    graficas.h \
    importar.h \
    latex.h \
    mainwindow.h \
    matriceswidget.h \
    matriz.h \
    nuevoproyecto.h

WIDGETS += \

    SOURCES += \
        variableswidget.cpp \
        viewmatriz.cpp

    HEADERS += \
        variableswidget.h \
        viewmatriz.h

FORMS += \
    etiquetas.ui \
    funcioneswidget.ui \
    graficas.ui \
    importar.ui \
    latex.ui \
    mainwindow.ui \
    matriceswidget.ui \
    nuevoproyecto.ui \
    variableswidget.ui \
    viewmatriz.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    iconos.qrc
