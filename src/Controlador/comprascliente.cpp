#include "comprascliente.h"
#include "qtimer.h"
#include "ui_comprascliente.h"
#include "qcombobox.h"
#include "qpropertyanimation.h"
#include "src/Modelo/dao/producto.h"
#include "carrito.h"
#include "src/Modelo/dao/cliente.h"
#include "asientos.h"
#include "vistacliente.h"
#include "abonos.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

bool ventanaCerrada2C = true;
bool ventanaCerrada2CP = true;

comprasCliente::comprasCliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::comprasCliente)
{
    ui->setupUi(this);
    mostrarVistaEventos();
    mostrarProductos();
}

comprasCliente::~comprasCliente()
{
    delete ui;

}

void comprasCliente::setCliente(Cliente cliente){
    this->cliente=cliente;
}

Cliente comprasCliente::getCliente(){
    return cliente;
}

void comprasCliente::on_menuBtn_clicked()
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
    if (ventanaCerrada2C){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerrada2C = false;


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
        ventanaCerrada2C = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();

}


void comprasCliente::on_pushButton_8_clicked()
{
    close();
}


void comprasCliente::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerrada2C){
        if(ventanaCerrada2CP){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada2CP = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada2CP = true;
        }
    } else{
        if(ventanaCerrada2CP){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada2CP = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada2CP = true;
        }
    }
    animation->start();

}


void comprasCliente::mostrarVistaEventos(){

    QVBoxLayout *menuDesp = new QVBoxLayout();

    QSqlQuery queryEventos;
    queryEventos.prepare("SELECT idEvento, nombre, descripcion, fecha, hora, tipo FROM eventos");

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
        QLabel *label6 = new QLabel(queryEventos.value("idEvento").toString());

        QPushButton *button = new QPushButton("Comprar");
        connect(button, &QPushButton::clicked, [=]() {
            asientos asientos;
            Evento *evento = new Evento(label6->text(), label1->text(), label2->text(), label3->text(), label4->text(), label5->text());
            cliente.listaEventos.push_back(evento);
            asientos.setCliente(cliente);
            asientos.setWindowFlags(Qt::FramelessWindowHint);
            asientos.setModal(true);
            hide();
            asientos.exec();
        });

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


void comprasCliente::mostrarProductos(){
    int cantidad=0;

    QVBoxLayout *menuDesp = new QVBoxLayout();

    QSqlQuery queryProductos;
    queryProductos.prepare("SELECT idProducto, nombre, cantidad, precio, descripcion, talla, color FROM productos");

    if (!queryProductos.exec()) {
        return;
    }


    while (queryProductos.next()) {
        QWidget *wid = new QWidget();
        QHBoxLayout *hor = new QHBoxLayout();
        QFrame *frame = new QFrame();
        QVBoxLayout *menuDesp2 = new QVBoxLayout();
        QComboBox *combo = new QComboBox();

        cantidad=queryProductos.value(2).toInt();
        for(int i=1; i<=cantidad; i++){
            combo->addItem(QString::number(i));
        }

        QLabel *label1 = new QLabel("Nombre: " + queryProductos.value("nombre").toString());
        QLabel *label2 = new QLabel("Precio: " + queryProductos.value("precio").toString());
        QLabel *label3 = new QLabel("Descripción: " +queryProductos.value("descripcion").toString());
        QLabel *label4 = new QLabel("Talla: " +queryProductos.value("talla").toString());
        QLabel *label5 = new QLabel("Color: " +queryProductos.value("color").toString());
        QLabel *label6 = new QLabel(queryProductos.value("idProducto").toString());

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
            QString idProducto= label6->text();
            QString nombre = label3->text();
            QString cantidad = combo->currentText();
            QString precio = label2->text();
            precio = precio.mid(8);
            QString talla = label4->text();
            QString color = label5->text();
            Producto *nuevoProducto = new Producto(idProducto, "", cantidad.toInt(), precio.toDouble(), nombre, talla, color);
            cliente.listaProductos.push_back(nuevoProducto);
            QDialog dialogoConfirmar(this);
            QLabel *labelConfirmar = new QLabel(" Producto añadido correctamente al carrito.");
            QVBoxLayout *layoutConfirmar = new QVBoxLayout;
            layoutConfirmar->addWidget(labelConfirmar);
            dialogoConfirmar.setLayout(layoutConfirmar);
            dialogoConfirmar.exec();

        });
    }
    ui->scrollAreaWidgetContents_3->setLayout(menuDesp);

}

void comprasCliente::setCarrito(QStringList añadirCarrito){
    this->añadirCarrito = añadirCarrito;
}

QStringList comprasCliente::getCarrito(){
    return añadirCarrito;
}


void comprasCliente::on_pushButton_3_clicked()
{
    carrito carrito;
    carrito.setCliente(cliente);
    carrito.setWindowFlags(Qt::FramelessWindowHint);
    carrito.setModal(true);
    hide();
    ventanaCerrada2C = true;
    ventanaCerrada2CP = true;
    carrito.imprimirCarrito();
    carrito.exec();

}

void comprasCliente::on_pushButton_4_clicked()
{
    vistaCliente vistaC;
    vistaC.setCliente(cliente);
    vistaC.setWindowFlags(Qt::FramelessWindowHint);
    vistaC.setModal(true);
    hide();
    ventanaCerrada2C = true;
    ventanaCerrada2CP = true;
    vistaC.exec();
}


void comprasCliente::on_pushButton_clicked()
{
    abonos abonos;
    abonos.setCliente(cliente);
    abonos.setWindowFlags(Qt::FramelessWindowHint);
    abonos.setModal(true);
    hide();
    abonos.exec();
}

