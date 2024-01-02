#include "login.h"
#include "registro.h"
#include "vistacliente.h"
#include "src/Controlador/registro.h"
#include "ui_login.h"
#include <QMessageBox>


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
    vistaCliente vistaCliente;
    vistaCliente.setWindowFlags(Qt::FramelessWindowHint);
    vistaCliente.setModal(true);
    vistaCliente.exec();
}

