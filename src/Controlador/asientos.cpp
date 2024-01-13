// asientos.cpp
#include "asientos.h"
#include "ui_asientos.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QRandomGenerator>

asientos::asientos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::asientos)
{
    ui->setupUi(this);
}

asientos::~asientos()
{
    delete ui;
}

int asientos::generarAsientos() {
    return QRandomGenerator::global()->bounded(1, 125);
}

void asientos::on_pushButton_4_clicked()
{
    int asiento = generarAsientos();

    QLabel *labelZona = new QLabel("Usted ha seleccionado Tribuna");
    QLabel *labelPrecio = new QLabel("El precio de las entradas es 20€");
    QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
    QPushButton *botonComprar = new QPushButton("Comprar");

    QVBoxLayout *layout = new QVBoxLayout;
    botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
    botonComprar->setFixedSize(85,30);
    labelZona->setStyleSheet("border:1px solid #01ff78;");
    labelPrecio->setStyleSheet("border:1px solid #01ff78;");
    labelAsiento->setStyleSheet("border:1px solid #01ff78;");
    layout->addWidget(labelZona);
    layout->addWidget(labelPrecio);
    layout->addWidget(labelAsiento);
    layout->addWidget(botonComprar);

    QDialog *nuevaVentana = new QDialog(this);
    nuevaVentana->setLayout(layout);

    nuevaVentana->exec();
}


