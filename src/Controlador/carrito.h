#ifndef CARRITO_H
#define CARRITO_H

#include <QDialog>
#include "cliente.h"
#include "src/Controlador/evento.h"

namespace Ui {
class carrito;
}

class carrito : public QDialog
{
    Q_OBJECT

public:

    explicit carrito(QWidget *parent = nullptr);
    ~carrito();
    bool ventanaCerrada = true;
    bool ventanaCerradaP = true;
    void imprimirCarrito();
    void setCliente(Cliente);
    Cliente getCliente();
    void setProducto(Producto);
    Producto getProducto();
    void setEvento(Evento);
    Evento getEvento();

private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();



    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::carrito *ui;
    Cliente cliente;
    Producto producto;
    Evento evento;
};

#endif // CARRITO_H
