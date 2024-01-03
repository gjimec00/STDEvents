#include "login.h"
#include "registro.h"
#include "administrador.h"
#include "vistacliente.h"
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
    QSqlQuery query;
    query.prepare("SELECT nombre FROM administrador WHERE nombre = :nombre AND contrasena = :contrasena");

    query.bindValue(":nombre", ui->lineEdit->text());
    query.bindValue(":contrasena", ui->lineEdit_2->text());

    if (query.exec() && query.next()) {
        QString nombreEnBaseDeDatos = query.value(0).toString();

        QString nombre = ui->lineEdit->text();
        if (nombreEnBaseDeDatos == nombre) {
            administrador administrador;
            administrador.setWindowFlags(Qt::FramelessWindowHint);
            administrador.setModal(true);
            administrador.exec();
        } else {
            vistaCliente vistaCliente;
            vistaCliente.setWindowFlags(Qt::FramelessWindowHint);
            vistaCliente.setModal(true);
            vistaCliente.exec();
        }
    } else {
        qDebug() << "Error en el inicio de sesión:" << query.lastError().text();
        QMessageBox::critical(this, "Error de inicio de sesión", "El usuario o la contraseña no coinciden");
    }
}





