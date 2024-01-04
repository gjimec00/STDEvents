#include "administrador.h"
#include <QParallelAnimationGroup>
#include "qpropertyanimation.h"
#include "ui_administrador.h"

bool ventanaCerrada = true;
bool ventanaCerradaP = true;
administrador::administrador(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::administrador)
{
    ui->setupUi(this);
    //ui->leftMenu->move(-220,1);
}

administrador::~administrador()
{
    delete ui;
}

void administrador::on_menuBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->leftMenu, "pos");
    animation->setDuration(500);
    QPropertyAnimation *animationDespl = new QPropertyAnimation(this, "geometry");
    animationDespl->setDuration(500);  // Duración en milisegundos
    QPropertyAnimation *animationMenu = new QPropertyAnimation(ui->mainBody, "pos");
    animationMenu->setDuration(500);
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->profileCont, "pos");
    animation2->setDuration(500);

    QRect geometry = this->geometry();
    if (ventanaCerrada){
        geometry.setWidth(1150);  // Doble del ancho actual
        geometry.setHeight(548);  // Doble de la altura actual
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0)); // Fuera de la vista
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0)); // Fuera de la vista
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0)); // Fuera de la vista
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerrada = false;


    } else{
        geometry.setWidth(930);  // Doble del ancho actual
        geometry.setHeight(548);  // Doble de la altura actual
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(0, 0)); // Fuera de la vista
        animation->setEndValue(QPoint(-220, 0));

        animationMenu->setStartValue(QPoint(220, 0)); // Fuera de la vista
        animationMenu->setEndValue(QPoint(0, 0));

        animation2->setStartValue(QPoint(1250, 0)); // Fuera de la vista
        animation2->setEndValue(QPoint(930, 0));
        ventanaCerrada = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();

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
        if(ventanaCerradaP){
            geometry.setWidth(1030);  // Doble del ancho actual
            geometry.setHeight(548);  // Doble de la altura actual
            animation->setEndValue(geometry);
            ventanaCerradaP = false;
        }else{
            geometry.setWidth(930);  // Doble del ancho actual
            geometry.setHeight(548);  // Doble de la altura actual
            animation->setEndValue(geometry);
            ventanaCerradaP = true;
        }
    } else{
        if(ventanaCerradaP){
            geometry.setWidth(1250);  // Doble del ancho actual
            geometry.setHeight(548);  // Doble de la altura actual
            animation->setEndValue(geometry);
            ventanaCerradaP = false;
        }else{
            geometry.setWidth(1150);  // Doble del ancho actual
            geometry.setHeight(548);  // Doble de la altura actual
            animation->setEndValue(geometry);
            ventanaCerradaP = true;
        }
    }
    animation->start();

}

