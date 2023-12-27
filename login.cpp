#include "login.h"
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

