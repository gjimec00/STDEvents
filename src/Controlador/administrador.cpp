#include "administrador.h"
#include "qpropertyanimation.h"
#include "ui_administrador.h"

administrador::administrador(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::administrador),
    ventanaCerrada(true)
{
    ui->setupUi(this);
}

administrador::~administrador()
{
    delete ui;
}

void administrador::on_menuBtn_clicked()
{

}


void administrador::on_pushButton_8_clicked()
{
    close();
}


void administrador::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);  // Duración en milisegundos
    QRect geometry = this->geometry();
    if (ventanaCerrada){
        geometry.setWidth(1030);  // Doble del ancho actual
        geometry.setHeight(548);  // Doble de la altura actual
        animation->setEndValue(geometry);
    } else{
        geometry.setWidth(929);  // Doble del ancho actual
        geometry.setHeight(548);  // Doble de la altura actual
        animation->setEndValue(geometry);
    }
    ventanaCerrada = !ventanaCerrada;
    animation->start();

}

