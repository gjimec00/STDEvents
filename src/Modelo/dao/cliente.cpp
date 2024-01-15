#include "cliente.h"

Cliente::Cliente() {}

Cliente::Cliente(QString nombre, QString apellidos, QString dni, int telefono, QString correo, QString contraseña, bool abonado, int numAsientoAbonado){
    this->nombre = nombre;
    this->apellidos = apellidos;
    this->dni = dni;
    this->telefono = telefono;
    this->correo = correo;
    this->contraseña = contraseña;
    this->abonado = abonado;
    this->numAsientoAb = numAsientoAbonado;
}
QString Cliente::getNombre(){
    return nombre;
}
QString Cliente::getApellidos(){
    return apellidos;
}
QString Cliente::getDNI(){
    return dni;
}
QString Cliente::getCorreo(){
    return correo;
}
QString Cliente::getContraseña(){
    return contraseña;
}
int Cliente::getTelefono(){
    return telefono;
}
int Cliente::getNumAsientoAb(){
    return numAsientoAb;
}
bool Cliente::getAbonado(){
    return abonado;
}

void Cliente::setNombre(QString nombre){
    this->nombre = nombre;
}
void Cliente::setApellidos(QString apellidos){
    this->apellidos = apellidos;
}
void Cliente::setDNI(QString dni){
    this->dni = dni;
}
void Cliente::setCorreo(QString correo){
    this->correo = correo;
}
void Cliente::setContraseña(QString contraseña){
    this->contraseña = contraseña;
}
void Cliente::setTelefono(int telefono){
    this->telefono = telefono;
}
void Cliente::setNumAsientoAb(int numAsientoAb){
    this->numAsientoAb = numAsientoAb;
}
void Cliente::setAbonado(bool abonado){
    this->abonado = abonado;
}
