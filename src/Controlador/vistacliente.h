#ifndef VISTACLIENTE_H
#define VISTACLIENTE_H

#include <QDialog>
#include "src/Modelo/dao/cliente.h"

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
    void setCliente(Cliente);
    Cliente getCliente();


private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();
    void on_pushButton_3_clicked();

    void on_calendarWidget_activated(const QDate &date);

    void on_pushButton_6_clicked();

private:
    Ui::vistaCliente *ui;
    Cliente cliente;



};

#endif // VISTACLIENTE_H
