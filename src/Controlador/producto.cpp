#include "producto.h"

Producto::Producto() {}

Producto::Producto(int idProducto, QString nombre, int cantidad, double precio, QString descripcion, QString talla, QString color){
    this->idProducto = idProducto;
    this->nombre = nombre;
    this->cantidad = cantidad;
    this->precio = precio;
    this->descripcion = descripcion;
    this->talla = talla;
    this->color = color;
}

int Producto::getIdProducto(){
    return idProducto;
}
QString Producto::getNombre(){
    return nombre;
}
int Producto::getCantidad(){
    return cantidad;
}
double Producto::getPrecio(){
    return precio;
}
QString Producto::getDescrpicion(){
    return descripcion;
}
QString Producto::getTalla(){
    return talla;
}
QString Producto::getColor(){
    return color;
}

void Producto::setIdProducto(int idProducto){
    this->idProducto = idProducto;
}
void Producto::setNombre(QString nombre){
    this->nombre = nombre;
}
void Producto::setCantidad(int cantidad){
    this->cantidad = cantidad;
}
void Producto::setPrecio(double precio){
    this->precio = precio;
}
void Producto::setDescrpicion(QString descripcion){
    this->descripcion = descripcion;
}
void Producto::setTalla(QString talla){
    this->talla = talla;
}
void Producto::setColor(QString color){
    this->color = color;
}
