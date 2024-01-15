#ifndef EVENTO_H
#define EVENTO_H
#include <QString>
#

class Evento
{
public:
    Evento();
    Evento(int idEvento, QString nombre, QString descripcion, QString fecha, QString hora, QString tipo);

    int getIdEvento();
    void setIdEvento(int idEvento);

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
    int idEvento;
    QString nombre;
    QString descripcion;
    QString fecha;
    QString hora;
    QString tipo;
};

#endif // EVENTO_H
