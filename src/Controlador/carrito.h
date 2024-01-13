#ifndef CARRITO_H
#define CARRITO_H

#include <QDialog>
#include "cliente.h"

namespace Ui {
class carrito;
}

class carrito : public QDialog
{
    Q_OBJECT

public:

    explicit carrito(QWidget *parent = nullptr);
    ~carrito();
    void imprimirCarrito();
    void setCliente(Cliente);
    Cliente getCliente();

private:
    Ui::carrito *ui;
    Cliente cliente;
};

#endif // CARRITO_H
