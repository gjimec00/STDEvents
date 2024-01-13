#ifndef COMPRASCLIENTE_H
#define COMPRASCLIENTE_H

#include <QDialog>

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

private:
    Ui::comprasCliente *ui;
private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();
    void on_pushButton_3_clicked();
};

#endif // COMPRASCLIENTE_H
