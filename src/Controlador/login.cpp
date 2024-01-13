#include "login.h"
#include "registro.h"
#include "administrador.h"
#include "vistacliente.h"
#include "src/Controlador/registro.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QtSql>
#include "entradasyabonos.h"
#include "cliente.h"


login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
    , mBaseDatos("stdevents",
                 "root",
                 "root",
                 "localhost",
                 3306)
{
    ui->setupUi(this);
    QString mensajeError;
    if (!mBaseDatos.abreConexion(mensajeError)){
        QMessageBox::critical(this, tr("Error"), mensajeError);
        close();
    }
}

login::~login()
{
    delete ui;
}



void login::on_exit_clicked()
{
    close();

}


void login::on_register_2_clicked()
{
    registro registro;
    registro.setWindowFlags(Qt::FramelessWindowHint);
    registro.setModal(true);
    registro.exec();

}

void login::on_login_2_clicked()
{
    comprobarUsuario();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void login::comprobarUsuario(){
    QSqlQuery query;

    // Comprobar si es un administrador
    query.prepare("SELECT nombre FROM administrador WHERE nombre = :nombre AND contrasena = :contrasena");
    query.bindValue(":nombre", ui->lineEdit->text());
    query.bindValue(":contrasena", ui->lineEdit_2->text());

    if (query.exec() && query.next()) {
        // Es un administrador
        abrirVistaAdministrador();
    } else {
        // No es un administrador, comprobar si es un cliente
        QSqlQuery query2;
        query2.prepare("SELECT nombre FROM clientes WHERE nombre = :nombre AND contrasena = :contrasena");
        query2.bindValue(":nombre", ui->lineEdit->text());
        query2.bindValue(":contrasena", ui->lineEdit_2->text());

        if(query2.exec() && query2.next()){
            // Es un cliente
            abrirVistaCliente();
        } else {
            // No es ni administrador ni cliente
            qDebug() << "Error en el inicio de sesión:" << query2.lastError().text();
            QMessageBox::critical(this, "Error de inicio de sesión", "<font color='white'>El usuario o la contraseña no coinciden</font>");
        }
    }
}

void login::abrirVistaAdministrador() {
    administrador admin;
    admin.setWindowFlags(Qt::FramelessWindowHint);
    admin.setModal(true);
    admin.exec();
}

void login::abrirVistaCliente() {
    vistaCliente cliente;
    cliente.setWindowFlags(Qt::FramelessWindowHint);
    cliente.setModal(true);
    cliente.exec();
}






