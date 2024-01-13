#include "vistacliente.h"
#include "qcombobox.h"
#include "ui_vistacliente.h"
#include "qpropertyanimation.h"
#include "calendario.h"
#include "producto.h"
#include "carrito.h"
#include "cliente.h"
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
    mostrarVistaEventos();
    mostrarProductos();
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


void vistaCliente::mostrarVistaEventos(){
    int numeroDeFilas = 0;
    QSqlQuery queryCount;
    queryCount.prepare("SELECT COUNT(*) FROM eventos");

    if (!queryCount.exec()) {
        return;
    }

    if (queryCount.next()) {
        numeroDeFilas = queryCount.value(0).toInt();
    }

    QVBoxLayout *menuDesp = new QVBoxLayout();

    QSqlQuery queryEventos;
    queryEventos.prepare("SELECT nombre, descripcion, fecha, hora, tipo FROM eventos");

    if (!queryEventos.exec()) {
        return;
    }

    while (queryEventos.next()) {
        QWidget *wid = new QWidget();
        QHBoxLayout *hor = new QHBoxLayout();
        QFrame *frame = new QFrame();
        QVBoxLayout *menuDesp2 = new QVBoxLayout();

        QLabel *label1 = new QLabel("Nombre: " +queryEventos.value("nombre").toString());
        QLabel *label2 = new QLabel("Descripción: " +queryEventos.value("descripcion").toString());
        QLabel *label3 = new QLabel("Fecha: " +queryEventos.value("fecha").toString());
        QLabel *label4 = new QLabel("Hora: " +queryEventos.value("hora").toString());
        QLabel *label5 = new QLabel("Tipo: " +queryEventos.value("tipo").toString());

        QPushButton *button = new QPushButton("Comprar");

        menuDesp2->addWidget(label1);
        menuDesp2->addWidget(label2);
        menuDesp2->addWidget(label3);
        menuDesp2->addWidget(label4);
        menuDesp2->addWidget(label5);
        button->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        button->setFixedSize(85,30);
        frame->setLayout(menuDesp2);
        hor->addWidget(frame);
        hor->addWidget(button);
        wid->setStyleSheet("border:1px solid #01ff78;");
        wid->setLayout(hor);
        menuDesp->addWidget(wid);
    }

    ui->scrollAreaWidgetContents->setLayout(menuDesp);
}


void vistaCliente::mostrarProductos(){
    int numeroDeFilas = 0;
    int cantidad=0;
    QSqlQuery queryCount;
    queryCount.prepare("SELECT COUNT(*) FROM eventos");

    if (!queryCount.exec()) {
        return;
    }

    if (queryCount.next()) {
        numeroDeFilas = queryCount.value(0).toInt();
    }

    QVBoxLayout *menuDesp = new QVBoxLayout();

    QSqlQuery queryProductos;
    queryProductos.prepare("SELECT nombre, cantidad, precio, descripcion, talla, color FROM productos");

    if (!queryProductos.exec()) {
        return;
    }


    while (queryProductos.next()) {
        QWidget *wid = new QWidget();
        QHBoxLayout *hor = new QHBoxLayout();
        QFrame *frame = new QFrame();
        QVBoxLayout *menuDesp2 = new QVBoxLayout();
        QComboBox *combo = new QComboBox();

        cantidad=queryProductos.value(1).toInt();
        for(int i=1; i<=cantidad; i++){
            combo->addItem(QString::number(i));
        }

        QLabel *label1 = new QLabel("Nombre: " + queryProductos.value("nombre").toString());
        QLabel *label2 = new QLabel("Precio: " + queryProductos.value("precio").toString());
        QLabel *label3 = new QLabel("Descripción: " +queryProductos.value("descripcion").toString());
        QLabel *label4 = new QLabel("Talla: " +queryProductos.value("talla").toString());
        QLabel *label5 = new QLabel("Color: " +queryProductos.value("color").toString());

        QPushButton *button = new QPushButton("Comprar");

        menuDesp2->addWidget(label1);
        menuDesp2->addWidget(label2);
        menuDesp2->addWidget(label3);
        menuDesp2->addWidget(label4);
        menuDesp2->addWidget(label5);
        button->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        button->setFixedSize(85,30);
        frame->setLayout(menuDesp2);
        hor->addWidget(frame);
        combo->setFixedSize(65,15);
        hor->addWidget(combo);
        hor->addWidget(button);
        wid->setStyleSheet("border:1px solid grey;");
        wid->setLayout(hor);
        menuDesp->addWidget(wid);



        connect(button, &QPushButton::clicked, [=]() {
            int idProducto= 0;
            QString nombre = label1->text();
            QString cantidad = combo->currentText();
            QString precio = label2->text();
            QString talla = label4->text();
            QString color = label5->text();
            Producto *nuevoProducto = new Producto(idProducto, nombre, cantidad.toInt(), precio.toDouble(), "", talla, color);
            //listaProductos.push_back(nuevoProducto);

        });
    }
    ui->scrollAreaWidgetContents_3->setLayout(menuDesp);

}

void vistaCliente::setCarrito(QStringList añadirCarrito){
    this->añadirCarrito = añadirCarrito;
}

QStringList vistaCliente::getCarrito(){
    return añadirCarrito;
}


void vistaCliente::on_pushButton_3_clicked()
{
    carrito carrito;
    carrito.setWindowFlags(Qt::FramelessWindowHint);
    carrito.setModal(true);
    hide();
    carrito.exec();
}
