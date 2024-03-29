QT       += core gui sql quickwidgets
QT += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Controlador/abonos.cpp \
    src/Controlador/asientos.cpp \
    src/Controlador/carrito.cpp \
    src/Controlador/addproducto.cpp \
    src/Modelo/dao/cliente.cpp \
    src/Controlador/clients.cpp \
    src/Controlador/comprascliente.cpp \
    src/Modelo/dao/evento.cpp \
    src/Controlador/eventos.cpp \
    src/Controlador/inventario.cpp \
    src/Modelo/dao/producto.cpp \
    src/Controlador/calendario.cpp \
    src/Controlador/administrador.cpp \
    src/Controlador/registro.cpp \
    src/Controlador/login.cpp \
    src/Controlador/main.cpp \
    src/Modelo/conexion/database.cpp \
    src/Controlador/vistacliente.cpp \

HEADERS += \
    src/Controlador/abonos.h \
    src/Controlador/asientos.h \
    src/Controlador/carrito.h \
    src/Controlador/addproducto.h \
    src/Modelo/dao/cliente.h \
    src/Controlador/clients.h \
    src/Controlador/calendario.h \
    src/Controlador/administrador.h \
    src/Controlador/comprascliente.h \
    src/Modelo/dao/evento.h \
    src/Controlador/eventos.h \
    src/Controlador/inventario.h \
    src/Modelo/dao/producto.h \
    src/Controlador/registro.h \
    src/Controlador/login.h \
    src/Modelo/conexion/database.h \
    src/Controlador/vistacliente.h

FORMS += \
    src/Vista/abonos.ui \
    src/Vista/comprascliente.ui \
    src/Vista/asientos.ui \
    src/Vista/inventario.ui \
    src/Vista/carrito.ui \
    src/Vista/clients.ui \
    src/Vista/eventos.ui \
    src/Vista/addproducto.ui \
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

