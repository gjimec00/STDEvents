#ifndef COMPRASCLIENTE_H
#define COMPRASCLIENTE_H

#include <QDialog>
#include "cliente.h"
#include "evento.h"

namespace Ui {
class comprasCliente;
}

class comprasCliente : public QDialog
{
    Q_OBJECT

public:

    explicit comprasCliente(QWidget *parent = nullptr);
    ~comprasCliente();
    void mostrarVistaEventos();
    void mostrarProductos();
    void on_comprarProducto();
    QStringList añadirCarrito;
    void setCarrito(QStringList);
    QStringList getCarrito();
    void setCliente(Cliente);
    Cliente getCliente();
    void setEvento(Evento);
    Evento getEvento();

private:
    Ui::comprasCliente *ui;
    Cliente cliente;
    Evento evento;

private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // COMPRASCLIENTE_H
