#ifndef ABONOS_H
#define ABONOS_H

#include <QDialog>
#include "src/Modelo/dao/cliente.h"
#include "src/Modelo/dao/evento.h"
namespace Ui {
class abonos;
}

class abonos : public QDialog
{
    Q_OBJECT

public:
    explicit abonos(QWidget *parent = nullptr);
    ~abonos();
    void setEvento(Evento);
    Evento getEvento();
    void setCliente(Cliente);
    Cliente getCliente();

private slots:
    void on_pushButton_4_clicked();

    int generarAsientos(int min, int max);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::abonos *ui;
    Evento evento;
    Cliente cliente;
};

#endif // ABONOS_H
