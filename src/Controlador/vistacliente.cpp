#include "vistacliente.h"
#include "ui_vistacliente.h"
#include "calendario.h"
#include "entradasyabonos.h"
#include "compraproductos.h"

vistaCliente::vistaCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vistaCliente)
{
    ui->setupUi(this);
}

vistaCliente::~vistaCliente()
{
    delete ui;
}

void vistaCliente::on_pushButton_clicked()
{
    this->close();
}

void vistaCliente::on_pushButton_4_clicked()
{

    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
      }
}


void vistaCliente::on_pushButton_3_clicked()
{
    showMinimized();
}



void vistaCliente::on_pushButton_7_clicked()
{
    Calendario calendario;
    calendario.setWindowFlags(Qt::FramelessWindowHint);
    calendario.setModal(true);
    calendario.exec();
}


void vistaCliente::on_pushButton_8_clicked()
{
    entradasyabonos compraEntradas;
    compraEntradas.setWindowFlags(Qt::FramelessWindowHint);
    compraEntradas.setModal(true);
    compraEntradas.exec();
}


void vistaCliente::on_pushButton_5_clicked()
{
    entradasyabonos compraAbonos;
    compraAbonos.setWindowFlags(Qt::FramelessWindowHint);
    compraAbonos.setModal(true);
    compraAbonos.exec();

}


void vistaCliente::on_pushButton_6_clicked()
{
    compraProductos compraProductos;
    compraProductos.setWindowFlags(Qt::FramelessWindowHint);
    compraProductos.setModal(true);
    compraProductos.exec();
}

