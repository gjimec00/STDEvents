#include "eventos.h"
#include "ui_eventos.h"
#include <QPropertyAnimation>
#include "administrador.h"
#include "clients.h"
#include "addproducto.h"
#include <QMessageBox>
#include <QtSql>

bool ventanaCerrada3 = true;
bool ventanaCerrada3P = true;
eventos::eventos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::eventos)
{
    ui->setupUi(this);
}

eventos::~eventos()
{
    delete ui;
}

void eventos::on_menuBtn_clicked()
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
    if (ventanaCerrada3){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerrada3 = false;


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
        ventanaCerrada3 = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();

}


void eventos::on_pushButton_8_clicked()
{
    close();
}


void eventos::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerrada3){
        if(ventanaCerrada3P){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada3P = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada3P = true;
        }
    } else{
        if(ventanaCerrada3P){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada3P = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada3P = true;
        }
    }
    animation->start();

}

void eventos::on_pushButton_4_clicked()
{
    administrador admin;
    admin.setWindowFlags(Qt::FramelessWindowHint);
    admin.setModal(true);
    hide();
    admin.exec();
}

void eventos::on_pushButton_3_clicked()
{
    addproducto producto;
    producto.setWindowFlags(Qt::FramelessWindowHint);
    producto.setModal(true);
    hide();
    producto.exec();
}


void eventos::on_pushButton_5_clicked()
{
    clients cliente;
    cliente.setWindowFlags(Qt::FramelessWindowHint);
    cliente.setModal(true);
    hide();
    cliente.exec();
}


void eventos::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("INSERT INTO eventos (nombre, fecha, hora, descripcion, tipo) VALUES (:nombre, :fecha, :hora, :descripcion, :tipo)");

    query.bindValue(":nombre", ui->lineEdit_10->text());
    query.bindValue(":fecha", ui->dateEdit->text());
    query.bindValue(":hora", ui->timeEdit->text());
    query.bindValue(":descripcion", ui->lineEdit_12->text());
    query.bindValue(":tipo", ui->lineEdit_9->text());



    if (query.exec()) {
        qDebug() << "Evento añadido con éxito.";
    } else {
        qDebug() << "Error al añadir el evento:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "No se pudo añadir el evento");
    }

    query.clear();
    ui->lineEdit_10->clear();
    //ui->dateEdit->clear();
    //ui->timeEdit->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_9->clear();

}


void eventos::on_pushButton_7_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT idEvento FROM productos WHERE nombre = :nombre AND talla = :talla AND color = :color");


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

