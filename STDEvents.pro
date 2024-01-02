QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/controlador/compraproductos.cpp \
    src/Controlador/entradasyabonos.cpp \
    src/Controlador/calendario.cpp \
    src/Controlador/administrador.cpp \
    src/Controlador/registro.cpp \
    src/Controlador/login.cpp \
    src/Controlador/main.cpp \
    src/Modelo/database.cpp \
    src/Controlador/vistacliente.cpp \

HEADERS += \
    src/Controlador/compraproductos.h \
    src/Controlador/entradasyabonos.h \
    src/Controlador/calendario.h \
    src/Controlador/administrador.h \
    src/Controlador/registro.h \
    src/Controlador/login.h \
    src/Modelo/database.h \
    src/Controlador/vistacliente.h

FORMS += \
    src/Vista/compraproductos.ui \
    src/Vista/entradasyabonos.ui \
    src/Vista/calendario.ui \
    src/Vista/administrador.ui \
    src/Vista/registro.ui \
    src/Vista/login.ui \
    src/Vista/vistacliente.ui

QMAKE_CXXFLAGS += -std=gnu++14

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc

