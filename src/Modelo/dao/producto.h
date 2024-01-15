#ifndef PRODUCTO_H
#define PRODUCTO_H
#include <QString>
class Producto
{
public:
    Producto();
    Producto(QString idProducto, QString nombre, int cantidad, double precio, QString descripcion, QString talla, QString color);

    QString getIdProducto();
    QString getNombre();
    int getCantidad();
    double getPrecio();
    QString getDescrpicion();
    QString getTalla();
    QString getColor();

    void setIdProducto(QString idProducto);
    void setNombre(QString nombre);
    void setCantidad(int cantidad);
    void setPrecio(double precio);
    void setDescrpicion(QString descripcion);
    void setTalla(QString talla);
    void setColor(QString color);

private:
    QString idProducto;
    QString nombre;
    int cantidad;
    double precio;
    QString descripcion;
    QString talla;
    QString color;
};

#endif // PRODUCTO_H
