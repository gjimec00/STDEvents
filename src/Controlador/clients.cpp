#include "clients.h"
#include "ui_clients.h"
#include <QPropertyAnimation>
#include "administrador.h"
#include "addproducto.h"
#include "eventos.h"
#include <QMessageBox>
#include <QtSql>

bool ventanaCerrada4 = true;
bool ventanaCerrada4P = true;
clients::clients(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::clients)
{
    ui->setupUi(this);
}

clients::~clients()
{
    delete ui;
}

void clients::on_menuBtn_clicked()
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
    if (ventanaCerrada4){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerrada4 = false;


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
        ventanaCerrada4 = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();

}


void clients::on_pushButton_8_clicked()
{
    close();
}


void clients::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerrada4){
        if(ventanaCerrada4P){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada4P = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada4P = true;
        }
    } else{
        if(ventanaCerrada4P){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada4P = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada4P = true;
        }
    }
    animation->start();

}

void clients::on_pushButton_4_clicked()
{
    administrador admin;
    admin.setWindowFlags(Qt::FramelessWindowHint);
    admin.setModal(true);
    hide();
    ventanaCerrada4 = true;
    ventanaCerrada4P = true;
    admin.exec();
}

void clients::on_pushButton_3_clicked()
{
    addproducto producto;
    producto.setWindowFlags(Qt::FramelessWindowHint);
    producto.setModal(true);
    hide();
    ventanaCerrada4 = true;
    ventanaCerrada4P = true;
    producto.exec();
}

void clients::on_pushButton_6_clicked()
{
    eventos evento;
    evento.setWindowFlags(Qt::FramelessWindowHint);
    evento.setModal(true);
    hide();
    ventanaCerrada4 = true;
    ventanaCerrada4P = true;
    evento.exec();
}


void clients::verificarDni() {
    QString dni = ui->lineEdit_7->text();
    QString letras[23] = {"T", "R", "W", "A", "G", "M", "Y", "F", "P", "D", "X", "B", "N", "J", "Z", "S", "Q", "V", "H", "L", "C", "K", "E" };
    if( dni.length() == 9){
        QString letra = dni.at(8);
        dni.removeLast();
        int nums = dni.toInt();
        int resto = nums%23;
        if(letras[resto]!=letra){
            QMessageBox::warning(this, "Warning", "El DNI no es correcto");
            ui->lineEdit_7->clear();
        }
    }else{
        QMessageBox::warning(this, "Warning", "El DNI no es correcto");
        ui->lineEdit_7->clear();
    }

}

void clients::on_pushButton_clicked()
{

    verificarDni();

    QSqlQuery query;
    query.prepare("INSERT INTO clientes (nombre, apellidos, dni, correo, contrasena, telefono) VALUES (:nombre, :apellidos, :dni, :correo, :contrasena, :telefono)");

    query.bindValue(":nombre", ui->lineEdit_10->text());
    query.bindValue(":apellidos", ui->lineEdit_11->text());
    query.bindValue(":dni", ui->lineEdit_7->text());
    query.bindValue(":correo", ui->lineEdit_12->text());
    query.bindValue(":contrasena", ui->lineEdit_9->text());
    query.bindValue(":telefono", ui->lineEdit_13->text());



    if (query.exec()) {
        qDebug() << "Cliente añadido con éxito.";
    } else {
        qDebug() << "Error al añadir el cliente:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "No se pudo añadir el cliente");
    }

    query.clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_12->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_13->clear();
}


void clients::on_pushButton_7_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT nombre, apellidos FROM clientes WHERE dni = :dni");

    query.bindValue(":dni", ui->lineEdit_22->text());

    if(query.exec() && query.next()){

        QString nombre= query.value(0).toString();
        QString apellidos= query.value(1).toString();

        if((nombre==ui->lineEdit_18->text())&&(apellidos==ui->lineEdit_19->text())){
            query.prepare("DELETE FROM clientes WHERE dni = :dni");
            query.bindValue(":dni", ui->lineEdit_22->text());

            if (query.exec()) {
                int numRowsAffected = query.numRowsAffected();
                if (numRowsAffected > 0) {
                    qDebug() << "Liente eliminado con éxito. Filas afectadas:" << numRowsAffected;
                } else {
                    qDebug() << "No se encontró ningún cliente con los criterios especificados.";
                    QMessageBox::information(this, "Información", "No se encontró ningún cliente con los criterios especificados.");
                }
            } else {
                qDebug() << "Error al eliminar el producto:" << query.lastError().text();
                QMessageBox::critical(this, "Error", "No se pudo eliminar el cliente");
            }
        }else{
            qDebug() << "El nombre no coincide en base de datos:" << query.lastError().text();
            QMessageBox::critical(this, "Error", "No se pudo eliminar el cliente");
        }

    } else {
    qDebug() << "Error al obtener los datos en bbdd:" << query.lastError().text();
    QMessageBox::critical(this, "Error", "No se pudo obtener el cliente");
    }

    query.clear();
    ui->lineEdit_18->clear();
    ui->lineEdit_19->clear();
    ui->lineEdit_22->clear();


}

