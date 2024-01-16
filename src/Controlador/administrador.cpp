#include "administrador.h"
#include <QParallelAnimationGroup>
#include "qpropertyanimation.h"
#include "ui_administrador.h"
#include "addproducto.h"
#include "eventos.h"
#include "clients.h"
#include "login.h"
#include <QSqlQuery>


administrador::administrador(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::administrador)
{
    ui->setupUi(this);
    mostrarResumenes();
    mostrarUltEventos();
    mostrarUltProductos();
}

administrador::~administrador()
{
    delete ui;
}

void administrador::on_menuBtn_clicked()
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


void administrador::on_pushButton_8_clicked()
{
    close();
}


void administrador::on_accountBtn_clicked()
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


void administrador::on_pushButton_3_clicked()
{

    addproducto addproducto;
    addproducto.setWindowFlags(Qt::FramelessWindowHint);
    addproducto.setModal(true);
    hide();
    addproducto.exec();
}


void administrador::on_pushButton_6_clicked()
{
    eventos evento;
    evento.setWindowFlags(Qt::FramelessWindowHint);
    evento.setModal(true);
    hide();
    evento.exec();
}


void administrador::on_pushButton_5_clicked()
{
    clients clientes;
    clientes.setWindowFlags(Qt::FramelessWindowHint);
    clientes.setModal(true);
    hide();
    clientes.exec();
}

void administrador::mostrarResumenes(){
    QSqlQuery queryProductos;
    queryProductos.prepare("SELECT COUNT(*) FROM productos");

    if (!queryProductos.exec()) {
        return;
    }

    if (queryProductos.next()) {
        ui->label_5->setText(queryProductos.value(0).toString());
    }

    QSqlQuery queryEventos;
    queryEventos.prepare("SELECT COUNT(*) FROM eventos");

    if (!queryEventos.exec()) {
        return;
    }

    if (queryEventos.next()) {
        ui->label_8->setText(queryEventos.value(0).toString());
    }

    QSqlQuery queryClientes;
    queryClientes.prepare("SELECT COUNT(*) FROM clientes");

    if (!queryClientes.exec()) {
        return;
    }

    if (queryClientes.next()) {
        ui->label_11->setText(queryClientes.value(0).toString());
    }
}

void administrador::mostrarUltProductos(){
    QSqlQuery query;
    query.prepare("SELECT descripcion, talla, color, precio FROM productos ORDER BY idProducto DESC LIMIT 3");

    if (!query.exec()) {
        return;
    }

    // Obtener los resultados
    QStringList results;
    QStringList tallas;
    QStringList colores;
    QStringList precios;
    while (query.next()) {
        QString nombre = query.value("descripcion").toString();
        results.append(nombre);
        QString talla = query.value("talla").toString();
        tallas.append(talla);
        QString color = query.value("color").toString();
        colores.append(color);
        QString precio = query.value("precio").toString();
        precios.append(precio);
    }
    if(results.size() >= 3){
        ui->label_20->setText(results.at(0));
        ui->label_21->setText(results.at(1));
        ui->label_24->setText(results.at(2));
    }

    if(tallas.size() >= 3){
        ui->label_3->setText(tallas.at(0));
        ui->label_4->setText(tallas.at(1));
        ui->label_17->setText(tallas.at(2));
    }

    if(colores.size() >= 3){
        ui->label_18->setText(colores.at(0));
        ui->label_23->setText(colores.at(1));
        ui->label_26->setText(colores.at(2));
    }

    if(precios.size() >= 3){
        ui->label_19->setText(precios.at(0) + "€");
        ui->label_22->setText(precios.at(1) + "€");
        ui->label_25->setText(precios.at(2) + "€");
    }
}
void administrador::mostrarUltEventos(){
    QSqlQuery query;
    query.prepare("SELECT descripcion, fecha, hora, tipo FROM eventos ORDER BY idEvento DESC LIMIT 3");

    if (!query.exec()) {
        return;
    }

    // Obtener los resultados
    QStringList nombres;
    QStringList fechas;
    QStringList horas;
    QStringList tipos;
    while (query.next()) {
        QString nombre = query.value("descripcion").toString();
        nombres.append(nombre);
        QString fecha = query.value("fecha").toString();
        fechas.append(fecha);
        QString hora = query.value("hora").toString();
        horas.append(hora);
        QString tipo = query.value("tipo").toString();
        tipos.append(tipo);
    }
    if(nombres.size() >= 3){
        ui->label_53->setText(nombres.at(0));
        ui->label_56->setText(nombres.at(1));
        ui->label_50->setText(nombres.at(2));
    }

    if(fechas.size() >= 3){
        ui->label_51->setText(fechas.at(0));
        ui->label_55->setText(fechas.at(1));
        ui->label_54->setText(fechas.at(2));
    }

    if(horas.size() >= 3){
        ui->label_58->setText(horas.at(0));
        ui->label_59->setText(horas.at(1));
        ui->label_60->setText(horas.at(2));
    }

    if(tipos.size() >= 3){
        ui->label_61->setText(tipos.at(0));
        ui->label_62->setText(tipos.at(1));
        ui->label_63->setText(tipos.at(2));
    }
}
