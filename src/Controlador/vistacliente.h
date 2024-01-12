#ifndef VISTACLIENTE_H
#define VISTACLIENTE_H

#include <QDialog>

namespace Ui {
class vistaCliente;
}

class vistaCliente : public QDialog
{
    Q_OBJECT

public:
    explicit vistaCliente(QWidget *parent = nullptr);
    ~vistaCliente();
    void mostrarVistaEventos();
    void mostrarProductos();
    void on_comprarProducto();
    QStringList añadirCarrito;
    void setCarrito(QStringList);
    QStringList getCarrito();

private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();
    void on_pushButton_3_clicked();
    /*
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();
*/

private:
    Ui::vistaCliente *ui;

};

#endif // VISTACLIENTE_H
