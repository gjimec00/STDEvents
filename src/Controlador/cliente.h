#ifndef CLIENTE_H
#define CLIENTE_H
#include <QString>
#include "producto.h"
using namespace std;
class Cliente
{
public:
    Cliente();
    Cliente(QString nombre, QString apellidos, QString dni, int telefono, QString correo, QString contraseña, bool abonado, int numAsientoAbonado);

    QString getNombre();
    QString getApellidos();
    QString getDNI();
    QString getCorreo();
    QString getContraseña();
    int getTelefono();
    int getNumAsientoAb();
    bool getAbonado();

    void setNombre(QString nombre);
    void setApellidos(QString apellidos);
    void setDNI(QString dni);
    void setCorreo(QString correo);
    void setContraseña(QString contraseña);
    void setTelefono(int telefono);
    void setNumAsientoAb(int numAsientoAb);
    void setAbonado(bool abonado);

    vector <Producto *> listaProductos;
private:
    QString nombre;
    QString apellidos;
    QString dni;
    QString correo;
    QString contraseña;
    int telefono;
    int numAsientoAb;
    bool abonado;
};

#endif // CLIENTE_H
