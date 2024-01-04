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
    animationDespl->setDuration(500);
    QPropertyAnimation *animationMenu = new QPropertyAnimation(ui->mainBody, "pos");
    animationMenu->setDuration(500);
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->profileCont, "pos");
    animation2->setDuration(500);

    QRect geometry = this->geometry();
    if (ventanaCerrada){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerrada = false;


    } else{
        geometry.setWidth(930);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(0, 0));
        animation->setEndValue(QPoint(-220, 0));

        animationMenu->setStartValue(QPoint(220, 0));
        animationMenu->setEndValue(QPoint(0, 0));

        animation2->setStartValue(QPoint(1250, 0));
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
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerrada){
        if(ventanaCerradaP){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaP = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaP = true;
        }
    } else{
        if(ventanaCerradaP){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaP = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaP = true;
        }
    }
    animation->start();

}

