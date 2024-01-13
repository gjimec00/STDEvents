#include "addproducto.h"
#include "ui_addproducto.h"
#include <QPropertyAnimation>
#include "administrador.h"
#include "eventos.h"
#include "clients.h"
#include <QMessageBox>
#include <QtSql>
#include "inventario.h"

bool ventanaCerrada2 = true;
bool ventanaCerrada2P = true;
addproducto::addproducto(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addproducto)
{
    ui->setupUi(this);
}

addproducto::~addproducto()
{
    delete ui;
}

void addproducto::on_menuBtn_clicked()
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
    if (ventanaCerrada2){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerrada2 = false;


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
        ventanaCerrada2 = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();

}


void addproducto::on_pushButton_8_clicked()
{
    close();
}


void addproducto::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerrada2){
        if(ventanaCerrada2P){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada2P = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada2P = true;
        }
    } else{
        if(ventanaCerrada2P){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada2P = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada2P = true;
        }
    }
    animation->start();

}

void addproducto::on_pushButton_4_clicked()
{
    administrador admin;
    admin.setWindowFlags(Qt::FramelessWindowHint);
    admin.setModal(true);
    hide();
    ventanaCerrada2 = true;
    ventanaCerrada2P = true;
    admin.exec();
}



void addproducto::on_pushButton_6_clicked()
{
    eventos evento;
    evento.setWindowFlags(Qt::FramelessWindowHint);
    evento.setModal(true);
    hide();
    ventanaCerrada2 = true;
    ventanaCerrada2P = true;
    evento.exec();
}


void addproducto::on_pushButton_5_clicked()
{
    clients cliente;
    cliente.setWindowFlags(Qt::FramelessWindowHint);
    cliente.setModal(true);
    hide();
    ventanaCerrada2 = true;
    ventanaCerrada2P = true;
    cliente.exec();
}


void addproducto::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO productos (nombre, cantidad, precio, descripcion, talla, color) VALUES (:nombre, :cantidad, :precio, :descripcion, :talla, :color)");

    query.bindValue(":nombre", ui->lineEdit_10->text());
    query.bindValue(":cantidad", ui->lineEdit_11->text());
    query.bindValue(":precio", ui->lineEdit_7->text());
    query.bindValue(":descripcion", ui->lineEdit_12->text());
    query.bindValue(":talla", ui->lineEdit_9->text());
    query.bindValue(":color", ui->lineEdit_2->text());



    if (query.exec()) {
        qDebug() << "Producto añadido con éxito.";
    } else {
        qDebug() << "Error al añadir el producto:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "No se pudo añadir el producto");
    }

    query.clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_2->clear();
}


void addproducto::on_pushButton_7_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT idProducto,cantidad FROM productos WHERE nombre = :nombre AND talla = :talla AND color = :color");


    query.bindValue(":nombre", ui->lineEdit_18->text());
    query.bindValue(":cantidad", ui->lineEdit_19->text());
    query.bindValue(":talla", ui->lineEdit_22->text());
    query.bindValue(":color", ui->lineEdit_23->text());

    if (query.exec() && query.next()) {

        int idProducto = query.value(0).toInt();
        int cantidad = query.value(1).toInt();

        if(cantidad <= ui->lineEdit_19->text().toInt()){
            query.prepare("DELETE FROM productos WHERE idProducto = :idProducto");
            query.bindValue(":idProducto", idProducto);

            if (query.exec()) {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected > 0) {
                    qDebug() << "Producto eliminado con éxito. Filas afectadas:" << numRowsAffected;
                } else {
                    qDebug() << "No se encontró ningún producto con los criterios especificados.";
                    QMessageBox::information(this, "Información", "No se encontró ningún producto con los criterios especificados.");
                }
            } else {
                qDebug() << "Error al eliminar el producto:" << query.lastError().text();
                QMessageBox::critical(this, "Error", "No se pudo eliminar el producto");
            }
        }else{
            cantidad -=  ui->lineEdit_19->text().toInt();
            query.prepare("UPDATE productos SET cantidad= :cantidad WHERE idProducto = :idProducto");
            query.bindValue(":idProducto", idProducto);
            query.bindValue(":cantidad", cantidad);

            if (query.exec()) {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected > 0) {
                    qDebug() << "Cantidad del producto eliminada con éxito. Filas afectadas:" << numRowsAffected;
                } else {
                    qDebug() << "No se encontró ningún producto con los criterios especificados.";
                    QMessageBox::information(this, "Información", "No se encontró ningún producto con los criterios especificados.");
                }
            } else {
                qDebug() << "Error al eliminar el producto:" << query.lastError().text();
                QMessageBox::critical(this, "Error", "No se pudo eliminar el producto");
            }
        }

    } else {
        qDebug() << "Error al obtener el idProducto:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "No se pudo obtener el idProducto");
    }

    query.clear();
    ui->lineEdit_18->clear();
    ui->lineEdit_19->clear();
    ui->lineEdit_22->clear();
    ui->lineEdit_23->clear();

}


void addproducto::on_pushButton_9_clicked()
{
    inventario inv;
    inv.setWindowFlags(Qt::FramelessWindowHint);
    inv.setModal(true);
    hide();
    ventanaCerrada2 = true;
    ventanaCerrada2P = true;
    inv.exec();
}

