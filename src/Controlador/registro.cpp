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
    /*
    QSqlQuery query;
    query.prepare("INSERT INTO clientes (dni, nombre, apellidos, telefono, correo, contraseña) VALUES (:dni, :nombre, :apellidos, :telefono, :correo, :contraseña)");
    query.bindValue(":nombre", ui->lineEdit->text());
    query.bindValue(":apellidos", ui->lineEdit_2->text());
    query.bindValue(":dni", ui->lineEdit_3->text());
    query.bindValue(":telefono", ui->lineEdit_4->text());
    query.bindValue(":correo", ui->lineEdit_5->text());
    query.bindValue(":contraseña", ui->lineEdit_6->text());
    query.exec();

    close();
    */
    // Configuración de la base de datos MySQL
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);  // Puerto por defecto de MySQL
    db.setDatabaseName("stdevents");
    db.setUserName("root");
    db.setPassword("root");

    // Verificar la conexión a la base de datos
    if (!db.open()) {
        qDebug() << "Error al abrir la base de datos:" << db.lastError().text();
        return;
    }

    // Crear una consulta de inserción
    QSqlQuery query;
    query.prepare("INSERT INTO clientes (dni, nombre, apellidos, telefono, correo, contrasena, abonado) VALUES (:dni, :nombre, :apellidos, :telefono, :correo, :contrasena, :abonado)");

    // Asignar valores a los parámetros de la consulta
    query.bindValue(":nombre", ui->lineEdit->text());
    query.bindValue(":apellidos", ui->lineEdit_2->text());
    query.bindValue(":dni", ui->lineEdit_3->text());
    query.bindValue(":telefono", ui->lineEdit_4->text());
    query.bindValue(":correo", ui->lineEdit_5->text());
    query.bindValue(":contrasena", ui->lineEdit_6->text());
    query.bindValue(":abonado", "1");

    // Ejecutar la consulta
    if (query.exec()) {
        qDebug() << "Datos añadidos con éxito.";
    } else {
        qDebug() << "Error al añadir datos:" << query.lastError().text();
    }

    query.clear();
    // Cerrar la conexión a la base de datos
    db.close();

}


void registro::on_pushButton_3_clicked()
{
    close();
}

