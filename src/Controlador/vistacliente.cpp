#include "vistacliente.h"
#include "ui_vistacliente.h"
#include "qpropertyanimation.h"
#include "calendario.h"
#include "entradasyabonos.h"
#include "compraproductos.h"

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
/*
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
*/
