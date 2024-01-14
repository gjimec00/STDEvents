#include "carrito.h"
#include "qpropertyanimation.h"
#include "ui_carrito.h"
#include "cliente.h"
#include "producto.h"
#include "vistacliente.h"
#include <QTimer>
#include <iostream>

carrito::carrito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::carrito)
{
    ui->setupUi(this);

}

carrito::~carrito()
{
    delete ui;
}

void carrito::setCliente(Cliente cliente){
    this->cliente=cliente;
}

Cliente carrito::getCliente(){
    return cliente;
}


void carrito::on_menuBtn_clicked()
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
    if (ventanaCerrada){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerrada = false;


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
        ventanaCerrada = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();


}


void carrito::on_pushButton_8_clicked()
{
    close();
}


void carrito::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerrada){
        if(ventanaCerradaP){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaP = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaP = true;
        }
    } else{
        if(ventanaCerradaP){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaP = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaP = true;
        }
    }
    animation->start();

}

void carrito::imprimirCarrito(){
    qDebug() << "Imprimiendo el contenido del carrito...";
    QVBoxLayout *menuDesp = new QVBoxLayout();

    for(size_t i = 0; i < cliente.listaProductos.size(); i++){

        QWidget *wid = new QWidget();
        QHBoxLayout *hor = new QHBoxLayout();
        QFrame *frame = new QFrame();
        QVBoxLayout *menuDesp2 = new QVBoxLayout();

        Producto *producto = cliente.listaProductos[i];
        double precio1 = producto->getPrecio();
        QString valorQString = QString::number(precio1);

        QLabel *label1 = new QLabel(producto->getNombre());
        QLabel *label2 = new QLabel("Precio: " + QString::number(precio1));
        QLabel *label3 = new QLabel("Descripción: " + producto->getDescrpicion());
        QLabel *label4 = new QLabel(producto->getTalla());
        QLabel *label5 = new QLabel(producto->getColor());

        menuDesp2->addWidget(label1);
        menuDesp2->addWidget(label2);
        menuDesp2->addWidget(label3);
        menuDesp2->addWidget(label4);
        menuDesp2->addWidget(label5);
        frame->setLayout(menuDesp2);
        hor->addWidget(frame);
        wid->setStyleSheet("border:1px solid grey;");
        wid->setLayout(hor);
        menuDesp->addWidget(wid);

    }
    ui->scrollAreaWidgetContents_4->setLayout(menuDesp);
}



