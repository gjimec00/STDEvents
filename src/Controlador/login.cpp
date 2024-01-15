#include "login.h"
#include "registro.h"
#include "administrador.h"
#include "vistacliente.h"
#include "src/Modelo/dao/cliente.h"
#include "src/Controlador/registro.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QtSql>



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
    vistaCliente vistaClt;


    // Seleccionamos toda la información del cliente para poder crear el objeto cliente y setearlo en la vista
    QSqlQuery clientQuery;
    clientQuery.prepare("SELECT apellidos, dni, telefono, correo, abonado, numAsientoAbonado FROM clientes WHERE nombre = :nombre AND contrasena = :contrasena");
    clientQuery.bindValue(":nombre", ui->lineEdit->text());
    clientQuery.bindValue(":contrasena", ui->lineEdit_2->text());

    if(clientQuery.exec() && clientQuery.next()){
        //Creo variables con todo lo recibido del SELECT
        QString apellidos = clientQuery.value(0).toString();
        QString dni = clientQuery.value(1).toString();
        int telefono = clientQuery.value(2).toInt();
        QString correo = clientQuery.value(3).toString();
        bool abonado = clientQuery.value(4).toBool();
        int numAsientoAbonado = clientQuery.value(5).toInt();

        //Creo el cliente y le doy todos los valores que posee en base de datos
        Cliente cliente(ui->lineEdit->text(), apellidos, dni, telefono, correo, ui->lineEdit_2->text(),abonado, numAsientoAbonado);
        vistaClt.setCliente(cliente);
    }


    vistaClt.setWindowFlags(Qt::FramelessWindowHint);
    vistaClt.setModal(true);
    vistaClt.exec();
}






