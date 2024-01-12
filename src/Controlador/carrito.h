#ifndef CARRITO_H
#define CARRITO_H

#include <QDialog>

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

private:
    Ui::carrito *ui;
};

#endif // CARRITO_H
