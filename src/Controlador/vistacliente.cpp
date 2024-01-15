#include "vistacliente.h"
#include "qcombobox.h"
#include "ui_vistacliente.h"
#include "qpropertyanimation.h"
#include "calendario.h"
#include "src/Modelo/dao/producto.h"
#include "carrito.h"
#include "src/Modelo/dao/cliente.h"
#include "comprascliente.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
//#include "entradasyabonos.h"
//#include "compraproductos.h"

bool ventanaCerradaC = true;
bool ventanaCerradaCP = true;

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

//Getters & Setters

void vistaCliente::setCliente(Cliente cliente){
    this->cliente=cliente;
}

Cliente vistaCliente::getCliente(){
    return cliente;
}

void vistaCliente::on_menuBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->leftMenu, "pos");
    animation->setDuration(500);
    QPropertyAnimation *animationDespl = new QPropertyAnimation(this, "geometry");
    animationDespl->setDuration(500);
    QPropertyAnimation *animationMenu = new QPropertyAnimation(ui->mainBody, "pos");
    animationMenu->setDuration(500);
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->profileCont, "pos");
    animation2->setDuration(500);

    QRect geometry = this->geometry();
    if (ventanaCerradaC){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerradaC = false;


    } else{
        geometry.setWidth(930);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(0, 0));
        animation->setEndValue(QPoint(-220, 0));

        animationMenu->setStartValue(QPoint(220, 0));
        animationMenu->setEndValue(QPoint(0, 0));

        animation2->setStartValue(QPoint(1250, 0));
        animation2->setEndValue(QPoint(930, 0));
        ventanaCerradaC = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();

}


void vistaCliente::on_pushButton_8_clicked()
{
    close();
}


void vistaCliente::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerradaC){
        if(ventanaCerradaCP){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaCP = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaCP = true;
        }
    } else{
        if(ventanaCerradaCP){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaCP = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaCP = true;
        }
    }
    animation->start();

}

void vistaCliente::on_pushButton_3_clicked()
{
    carrito carrito;
    carrito.setCliente(cliente);
    carrito.setWindowFlags(Qt::FramelessWindowHint);
    carrito.setModal(true);
    hide();
    ventanaCerradaC = true;
    ventanaCerradaCP = true;
    carrito.exec();
}

void vistaCliente::on_calendarWidget_activated(const QDate &date)
{
    QSqlQuery query;
    query.prepare("SELECT nombre, fecha, hora, descripcion, tipo FROM eventos WHERE fecha = :fecha");
    query.bindValue(":fecha", date);

    if (!query.exec()) {
        return;
    }
    QStringList resultados;
    // Procesar los resultados
    while (query.next()) {
        QString col1 = query.value(0).toString();
        QString col2 = query.value(1).toString();
        QString col3 = query.value(2).toString();
        QString col4 = query.value(3).toString();
        QString col5 = query.value(4).toString();
        QString resultado = "Nombre del evento: " + col1 + ", fecha: " + col2 + ", hora: " + col3 + ", descripcion: " + col4 + ", tipo: " + col5;
        resultados.append(resultado);
    }
    if (!resultados.isEmpty())    {
        QString resultadosStr = resultados.join("\n");
        ui->label_2->setText(resultadosStr);
    }else{
        ui->label_2->setText("No hay eventos programados disponibles para este día");
    }
}


void vistaCliente::on_pushButton_6_clicked()
{
    comprasCliente compras;
    compras.setCliente(cliente);
    compras.setWindowFlags(Qt::FramelessWindowHint);
    compras.setModal(true);
    hide();
    ventanaCerradaC = true;
    ventanaCerradaCP = true;
    compras.exec();
}

