#include "registro.h"
#include "ui_registro.h"
#include <QMessageBox>
#include <QtSql>

registro::registro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registro)
{
    ui->setupUi(this);

}

registro::~registro()
{
    delete ui;
}

void registro::verificarContraseñas() {
    QString password = ui->lineEdit_6->text();
    QString confirmedPass = ui->lineEdit_7->text();

    if (password != confirmedPass) {
        QMessageBox::warning(this, "Warning", "The passwords you've entered don't match each other.");
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
    }
}

void registro::on_pushButton_clicked()
{
    verificarContraseñas();

    QSqlQuery query;
    query.prepare("INSERT INTO clientes (dni, nombre, apellidos, telefono, correo, contrasena, abonado) VALUES (:dni, :nombre, :apellidos, :telefono, :correo, :contrasena, :abonado)");

    query.bindValue(":nombre", ui->lineEdit->text());
    query.bindValue(":apellidos", ui->lineEdit_2->text());
    query.bindValue(":dni", ui->lineEdit_3->text());
    query.bindValue(":telefono", ui->lineEdit_4->text());
    query.bindValue(":correo", ui->lineEdit_5->text());
    query.bindValue(":contrasena", ui->lineEdit_6->text());


    if (query.exec()) {
        qDebug() << "Datos añadidos con éxito.";
    } else {
        qDebug() << "Error al añadir datos:" << query.lastError().text();
    }

    query.clear();

}


void registro::on_pushButton_3_clicked()
{
    close();
}

