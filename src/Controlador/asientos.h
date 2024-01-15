#ifndef ASIENTOS_H
#define ASIENTOS_H

#include <QDialog>
#include "evento.h"
#include "cliente.h"

namespace Ui {
class asientos;
}

class asientos : public QDialog
{
    Q_OBJECT

public:
    explicit asientos(QWidget *parent = nullptr);
    ~asientos();
    void setEvento(Evento);
    Evento getEvento();
    void setCliente(Cliente);
    Cliente getCliente();

private slots:
    void on_pushButton_4_clicked();

    QVector<int> generarAsientos(int min, int max, int cantidadEntradas);

    void mostrarMensajeNoAsientosDisponibles();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();


private:
    Evento evento;
    Cliente cliente;
    Ui::asientos *ui;
};

#endif // ASIENTOS_H
