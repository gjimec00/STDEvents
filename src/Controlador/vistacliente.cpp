#include "vistacliente.h"
#include "ui_vistacliente.h"
#include "qpropertyanimation.h"
#include "calendario.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
//#include "entradasyabonos.h"
//#include "compraproductos.h"

bool ventanaCerradaC = true;
bool ventanaCerradaCP = true;

vistaCliente::vistaCliente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vistaCliente)
{
    ui->setupUi(this);
    mostrarVistaEventos();
}

vistaCliente::~vistaCliente()
{
    delete ui;
}

void vistaCliente::on_menuBtn_clicked()
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
    if (ventanaCerradaC){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerradaC = false;


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
        ventanaCerradaC = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();

}


void vistaCliente::on_pushButton_8_clicked()
{
    close();
}


void vistaCliente::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerradaC){
        if(ventanaCerradaCP){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaCP = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaCP = true;
        }
    } else{
        if(ventanaCerradaCP){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaCP = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerradaCP = true;
        }
    }
    animation->start();

}


void vistaCliente::mostrarVistaEventos(){
    int numeroDeFilas = 0;
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM eventos");

    if (!query.exec()) {
        return;
    }
    // Obtener el resultado
    if (query.next()) {
        numeroDeFilas = query.value(0).toInt();
    }

    QVBoxLayout *menuDesp = new QVBoxLayout();
    for (int i = 0; i < numeroDeFilas; i++){
        QWidget * wid = new QWidget();
        QHBoxLayout * hor = new QHBoxLayout();
        QFrame * frame = new QFrame();
        QVBoxLayout *menuDesp2 = new QVBoxLayout();
        QLabel * label1 = new QLabel("Prueba1");
        QLabel * label2 = new QLabel("Prueba2");
        QLabel * label3 = new QLabel("Prueba3");
        QLabel * label4 = new QLabel("Prueba4");
        QLabel * label5 = new QLabel("Prueba5");
        QPushButton * button = new QPushButton("Comprar");
        wid->setLayout(hor);
        frame->setLayout(menuDesp2);
        menuDesp2->addWidget(label1);
        menuDesp2->addWidget(label2);
        menuDesp2->addWidget(label3);
        menuDesp2->addWidget(label4);
        menuDesp2->addWidget(label5);
        hor->addWidget(frame);
        hor->addWidget(button);
        menuDesp->addWidget(wid);
    }
    ui->scrollAreaWidgetContents->setLayout(menuDesp);
}
