#include "evento.h"

Evento::Evento() {}

Evento::Evento(int idEvento){
    this->idEvento = idEvento;
}

int Evento::getIdEvento(){
    return idEvento;
}

void Evento::setIdEvento(int idEvento){
    this->idEvento = idEvento;
}

QString Evento::getNombre(){
    return nombre;
}

void Evento::setNombre(QString nombre){
    this->nombre = nombre;
}

QString Evento::getDescripcion(){
    return descripcion;
}

void Evento::setDescripcion(QString descripcion){
    this->descripcion = descripcion;
}

QString Evento::getFecha(){
    return fecha;
}

void Evento::setFecha(QString fecha){
    this->fecha = fecha;
}

QString Evento::getHora(){
    return hora;
}

void Evento::setHora(QString hora){
    this->hora = hora;
}

QString Evento::getTipo(){
    return tipo;
}

void Evento::setTipo(QString tipo){
    this->tipo = tipo;
}


