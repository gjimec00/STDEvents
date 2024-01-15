#ifndef ABONOS_H
#define ABONOS_H

#include <QDialog>
#include "cliente.h"
#include "evento.h"
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

    QVector<int> generarAsientos(int min, int max, int cantidadEntradas);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();
    Evento evento;
    Cliente cliente;

private:
    Ui::abonos *ui;
};

#endif // ABONOS_H
