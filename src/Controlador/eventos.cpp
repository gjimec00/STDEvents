#include "eventos.h"
#include "ui_eventos.h"
#include <QPropertyAnimation>
#include "administrador.h"
#include "clients.h"
#include "addproducto.h"
#include <QMessageBox>
#include <QtSql>
#include "calendario.h"

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
    ventanaCerrada3 = true;
    ventanaCerrada3P = true;
    admin.exec();
}

void eventos::on_pushButton_3_clicked()
{
    addproducto producto;
    producto.setWindowFlags(Qt::FramelessWindowHint);
    producto.setModal(true);
    hide();
    ventanaCerrada3 = true;
    ventanaCerrada3P = true;
    producto.exec();
}


void eventos::on_pushButton_5_clicked()
{
    clients cliente;
    cliente.setWindowFlags(Qt::FramelessWindowHint);
    cliente.setModal(true);
    hide();
    ventanaCerrada3 = true;
    ventanaCerrada3P = true;
    cliente.exec();
}


void eventos::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT dni FROM administrador WHERE nombre='admin'");

    if (query.exec() && query.next()) {

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
    } else {
        qDebug() << "Error al obtener el idEvento:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "No se pudo obtener el idEvento");
    }


    query.clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_9->clear();

}


void eventos::on_pushButton_7_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT idEvento, fecha, hora, descripcion FROM eventos WHERE nombre = :nombre");

    query.bindValue(":nombre", ui->lineEdit_18->text());

    if (query.exec() && query.next()) {

        int idEvento = query.value(0).toInt();
        QString fecha = query.value(1).toString();
        QString hora = query.value(2).toString();
        QString descripcion = query.value(3).toString();


        //Query de modificacion de la fecha
        if(ui->dateEdit_2->text() != fecha && ui->dateEdit_2->text()!= "2023-10-14"){
            query.prepare("UPDATE eventos SET fecha= :fecha WHERE idEvento = :idEvento");
            query.bindValue(":idEvento", idEvento);
            query.bindValue(":fecha", ui->dateEdit_2->text());

            if (query.exec()) {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected > 0) {
                    qDebug() << "Fecha del evento modificada con éxito. Filas afectadas:" << numRowsAffected;
                } else {
                    qDebug() << "No se encontró ningún evento con los criterios especificados. FECHA";
                    QMessageBox::information(this, "Información", "No se encontró ningún evento con los criterios especificados.");
                }
            } else {
                qDebug() << "Error al modificar la fecha del evento:" << query.lastError().text();
                QMessageBox::critical(this, "Error", "No se pudo modificar el evento");
            }
        }

        //Query de modificacion de la hora
        if(ui->timeEdit_2->text() != hora && ui->timeEdit_2->text()!="00:00:00"){
            query.prepare("UPDATE eventos SET hora= :hora WHERE idEvento = :idEvento");
            query.bindValue(":idEvento", idEvento);
            query.bindValue(":hora", ui->timeEdit_2->text());

            if (query.exec()) {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected > 0) {
                    qDebug() << "Hora del evento modificada con éxito. Filas afectadas:" << numRowsAffected;
                } else {
                    qDebug() << "No se encontró ningún evento con los criterios especificados. HORA";
                    QMessageBox::information(this, "Información", "No se encontró ningún evento con los criterios especificados.");
                }
            } else {
                qDebug() << "Error al modificar la hora del evento:" << query.lastError().text();
                QMessageBox::critical(this, "Error", "No se pudo modificar el evento");
            }
        }

        //Query de modificacion de la descripción
        if(ui->lineEdit_23->text() != descripcion && ui->lineEdit_23->text()!=""){
            query.prepare("UPDATE eventos SET descripcion= :descripcion WHERE idEvento = :idEvento");
            query.bindValue(":idEvento", idEvento);
            query.bindValue(":descripcion", ui->lineEdit_23->text());

            if (query.exec()) {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected > 0) {
                    qDebug() << "Descripción del evento modificada con éxito. Filas afectadas:" << numRowsAffected;
                } else {
                    qDebug() << "No se encontró ningún evento con los criterios especificados. DESCRIPCION";
                    QMessageBox::information(this, "Información", "No se encontró ningún evento con los criterios especificados.");
                }
            } else {
                qDebug() << "Error al modificar la descripción del evento:" << query.lastError().text();
                QMessageBox::critical(this, "Error", "No se pudo modificar el evento");
            }
        }

    } else {
        qDebug() << "Error al obtener el idEvento:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "No se pudo obtener el idEvento");
    }

    query.clear();
    ui->lineEdit_18->clear();
    ui->lineEdit_23->clear();

}


void eventos::on_pushButton_9_clicked()
{
    Calendario calendario;
    calendario.setWindowFlags(Qt::FramelessWindowHint);
    calendario.setModal(true);
    ventanaCerrada3 = true;
    ventanaCerrada3P = true;
    calendario.exec();
}

