#ifndef EVENTO_H
#define EVENTO_H
#include <QString>
#

class Evento
{
public:
    Evento();
    Evento(QString idEvento, QString nombre, QString descripcion, QString fecha, QString hora, QString tipo);

    QString getIdEvento();
    void setIdEvento(QString idEvento);

    QString getNombre();
    QString getDescripcion();
    QString getFecha();
    QString getHora();
    QString getTipo();

    void setNombre(QString nombre);
    void setDescripcion(QString descrpicion);
    void setFecha(QString fecha);
    void setHora(QString hora);
    void setTipo(QString Tipo);


private:
    QString idEvento;
    QString nombre;
    QString descripcion;
    QString fecha;
    QString hora;
    QString tipo;
};

#endif // EVENTO_H
