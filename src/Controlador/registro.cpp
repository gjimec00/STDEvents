#include "registro.h"
#include "ui_registro.h"
#include <QMessageBox>

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
}

