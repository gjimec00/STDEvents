// asientos.cpp
#include "asientos.h"
#include "ui_asientos.h"
#include "comprascliente.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QRandomGenerator>
#include <QtSql>

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

void asientos::setEvento(Evento evento){
    this->evento = evento;
}

Evento asientos::getEvento(){
    return evento;
}

int asientos::generarAsientos() {
    QSqlQuery asientosQuery;
    QVector<int> asientosOcupados;
    int numAsiento;

    asientosQuery.prepare("SELECT numAsiento FROM asientos");
    if (asientosQuery.exec()) {
        while (asientosQuery.next()) {
            asientosOcupados.append(asientosQuery.value("numAsiento").toInt());
        }
    }
    do {
        numAsiento = QRandomGenerator::global()->bounded(1, 125);
    } while (asientosOcupados.contains(numAsiento));

    return numAsiento;
}

void asientos::on_pushButton_4_clicked()
{
    int precio = 50;

    QDialog dialogoEntradas(this);

    QLabel *labelCantidad = new QLabel("Número de Entradas: ");
    QSpinBox *spinBoxEntradas = new QSpinBox();
    QLabel *labelZona = new QLabel("Usted ha seleccionado Tribuna ");
    QLabel *labelCoste = new QLabel("El coste de las Entradas en este sector es de 50€ ");
    spinBoxEntradas->setRange(1, 10);
    labelCantidad->setBuddy(spinBoxEntradas);

    QVBoxLayout *layoutEntradas = new QVBoxLayout;
    layoutEntradas->addWidget(labelZona);
    layoutEntradas->addWidget(labelCoste);
    layoutEntradas->addWidget(labelCantidad);
    layoutEntradas->addWidget(spinBoxEntradas);

    QDialogButtonBox *botonesEntradas = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layoutEntradas->addWidget(botonesEntradas);
    connect(botonesEntradas, &QDialogButtonBox::accepted, &dialogoEntradas, &QDialog::accept);
    connect(botonesEntradas, &QDialogButtonBox::rejected, &dialogoEntradas, &QDialog::reject);

    dialogoEntradas.setLayout(layoutEntradas);

    if (dialogoEntradas.exec() == QDialog::Accepted) {
        int cantidadEntradas = spinBoxEntradas->value();
        int precioTotal = precio * cantidadEntradas;

        QLabel *labelPrecioTotal = new QLabel("Precio Total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;
        QLabel *labelSector = new QLabel("Sector: Tribuna");
        layoutAsientos->addWidget(labelSector);

        QVector<int> asientosGenerados;
        for (int i = 0; i < cantidadEntradas; ++i) {
            int asiento = generarAsientos();

            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
            layoutAsientos->addWidget(labelAsiento);

            asientosGenerados.append(asiento);
        }

        layoutAsientos->addWidget(labelPrecioTotal);

        QHBoxLayout *layoutBotones = new QHBoxLayout;

        QPushButton *botonComprar = new QPushButton("Comprar");
        botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        botonComprar->setFixedSize(120,30);
        layoutBotones->addWidget(botonComprar);

        QPushButton *botonCancelar = new QPushButton("Cancelar Compra");
        botonCancelar->setStyleSheet("background-color:#ff6347; color:#fff; border-radius:10px;");
        botonCancelar->setFixedSize(120,30);
        layoutBotones->addWidget(botonCancelar);

        layoutAsientos->addLayout(layoutBotones);

        QDialog *nuevaVentana = new QDialog(this);
        nuevaVentana->setLayout(layoutAsientos);

        connect(botonComprar, &QPushButton::clicked, [=]() {
            for (int i = 0; i < cantidadEntradas; ++i) {
                QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento)  VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asientosGenerados.at(i));
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", evento.getIdEvento());

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            nuevaVentana->accept();
        });

        connect(botonCancelar, &QPushButton::clicked, nuevaVentana, &QDialog::reject);

        if (nuevaVentana->exec() == QDialog::Accepted) {
            qDebug() << "Compra realizada con éxito.";
        } else {
            qDebug() << "Se canceló la compra. No se guardará en la base de datos.";
        }
    } else {
        qDebug() << "No se seleccionaron entradas.";
    }
}


void asientos::on_pushButton_3_clicked()
{
    int precio = 40;

    QDialog dialogoEntradas(this);

    QLabel *labelCantidad = new QLabel("Número de Entradas: ");
    QSpinBox *spinBoxEntradas = new QSpinBox();
    QLabel *labelZona = new QLabel("Usted ha seleccionado Preferente ");
    QLabel *labelCoste = new QLabel("El coste de las Entradas en este sector es de 40€ ");
    spinBoxEntradas->setRange(1, 10);
    labelCantidad->setBuddy(spinBoxEntradas);

    QVBoxLayout *layoutEntradas = new QVBoxLayout;
    layoutEntradas->addWidget(labelZona);
    layoutEntradas->addWidget(labelCoste);
    layoutEntradas->addWidget(labelCantidad);
    layoutEntradas->addWidget(spinBoxEntradas);

    QDialogButtonBox *botonesEntradas = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layoutEntradas->addWidget(botonesEntradas);
    connect(botonesEntradas, &QDialogButtonBox::accepted, &dialogoEntradas, &QDialog::accept);
    connect(botonesEntradas, &QDialogButtonBox::rejected, &dialogoEntradas, &QDialog::reject);

    dialogoEntradas.setLayout(layoutEntradas);

    if (dialogoEntradas.exec() == QDialog::Accepted) {
        int cantidadEntradas = spinBoxEntradas->value();
        int precioTotal = precio * cantidadEntradas;

        QLabel *labelPrecioTotal = new QLabel("Precio Total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;
        QLabel *labelSector = new QLabel("Sector: Preferente");
        layoutAsientos->addWidget(labelSector);

        QVector<int> asientosGenerados;
        for (int i = 0; i < cantidadEntradas; ++i) {
            int asiento = generarAsientos();

            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
            layoutAsientos->addWidget(labelAsiento);

            asientosGenerados.append(asiento);
        }

        layoutAsientos->addWidget(labelPrecioTotal);

        QHBoxLayout *layoutBotones = new QHBoxLayout;

        QPushButton *botonComprar = new QPushButton("Comprar");
        botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        botonComprar->setFixedSize(120,30);
        layoutBotones->addWidget(botonComprar);

        QPushButton *botonCancelar = new QPushButton("Cancelar Compra");
        botonCancelar->setStyleSheet("background-color:#ff6347; color:#fff; border-radius:10px;");
        botonCancelar->setFixedSize(120,30);
        layoutBotones->addWidget(botonCancelar);

        layoutAsientos->addLayout(layoutBotones);

        QDialog *nuevaVentana = new QDialog(this);
        nuevaVentana->setLayout(layoutAsientos);

        connect(botonComprar, &QPushButton::clicked, [=]() {
            for (int i = 0; i < cantidadEntradas; ++i) {
                QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio) VALUES (:numAsiento, :precio)");
                insertQuery.bindValue(":numAsiento", asientosGenerados.at(i));
                insertQuery.bindValue(":precio", precio);

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            nuevaVentana->accept();
        });

        connect(botonCancelar, &QPushButton::clicked, nuevaVentana, &QDialog::reject);

        if (nuevaVentana->exec() == QDialog::Accepted) {
            qDebug() << "Compra realizada con éxito.";
        } else {
            qDebug() << "Se canceló la compra. No se guardará en la base de datos.";
        }
    } else {
        qDebug() << "No se seleccionaron entradas.";
    }
}






void asientos::on_pushButton_2_clicked()
{
    int precio = 25;

    QDialog dialogoEntradas(this);

    QLabel *labelCantidad = new QLabel("Número de Entradas: ");
    QSpinBox *spinBoxEntradas = new QSpinBox();
    QLabel *labelZona = new QLabel("Usted ha seleccionado Fondo Norte ");
    QLabel *labelCoste = new QLabel("El coste de las Entradas en este sector es de 25€ ");
    spinBoxEntradas->setRange(1, 10);
    labelCantidad->setBuddy(spinBoxEntradas);

    QVBoxLayout *layoutEntradas = new QVBoxLayout;
    layoutEntradas->addWidget(labelZona);
    layoutEntradas->addWidget(labelCoste);
    layoutEntradas->addWidget(labelCantidad);
    layoutEntradas->addWidget(spinBoxEntradas);

    QDialogButtonBox *botonesEntradas = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layoutEntradas->addWidget(botonesEntradas);
    connect(botonesEntradas, &QDialogButtonBox::accepted, &dialogoEntradas, &QDialog::accept);
    connect(botonesEntradas, &QDialogButtonBox::rejected, &dialogoEntradas, &QDialog::reject);

    dialogoEntradas.setLayout(layoutEntradas);

    if (dialogoEntradas.exec() == QDialog::Accepted) {
        int cantidadEntradas = spinBoxEntradas->value();
        int precioTotal = precio * cantidadEntradas;

        QLabel *labelPrecioTotal = new QLabel("Precio Total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;
        QLabel *labelSector = new QLabel("Sector: Fondo Norte");
        layoutAsientos->addWidget(labelSector);

        QVector<int> asientosGenerados;
        for (int i = 0; i < cantidadEntradas; ++i) {
            int asiento = generarAsientos();

            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
            layoutAsientos->addWidget(labelAsiento);

            asientosGenerados.append(asiento);
        }

        layoutAsientos->addWidget(labelPrecioTotal);

        QHBoxLayout *layoutBotones = new QHBoxLayout;

        QPushButton *botonComprar = new QPushButton("Comprar");
        botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        botonComprar->setFixedSize(120,30);
        layoutBotones->addWidget(botonComprar);

        QPushButton *botonCancelar = new QPushButton("Cancelar Compra");
        botonCancelar->setStyleSheet("background-color:#ff6347; color:#fff; border-radius:10px;");
        botonCancelar->setFixedSize(120,30);
        layoutBotones->addWidget(botonCancelar);

        layoutAsientos->addLayout(layoutBotones);

        QDialog *nuevaVentana = new QDialog(this);
        nuevaVentana->setLayout(layoutAsientos);

        connect(botonComprar, &QPushButton::clicked, [=]() {
            for (int i = 0; i < cantidadEntradas; ++i) {
                QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio) VALUES (:numAsiento, :precio)");
                insertQuery.bindValue(":numAsiento", asientosGenerados.at(i));
                insertQuery.bindValue(":precio", precio);

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            nuevaVentana->accept();
        });

        connect(botonCancelar, &QPushButton::clicked, nuevaVentana, &QDialog::reject);

        if (nuevaVentana->exec() == QDialog::Accepted) {
            qDebug() << "Compra realizada con éxito.";
        } else {
            qDebug() << "Se canceló la compra. No se guardará en la base de datos.";
        }
    } else {
        qDebug() << "No se seleccionaron entradas.";
    }
}


void asientos::on_pushButton_clicked()
{
    int precio = 25;

    QDialog dialogoEntradas(this);

    QLabel *labelCantidad = new QLabel("Número de Entradas: ");
    QSpinBox *spinBoxEntradas = new QSpinBox();
    QLabel *labelZona = new QLabel("Usted ha seleccionado Fondo Sur ");
    QLabel *labelCoste = new QLabel("El coste de las Entradas en este sector es de 25€ ");
    spinBoxEntradas->setRange(1, 10);
    labelCantidad->setBuddy(spinBoxEntradas);

    QVBoxLayout *layoutEntradas = new QVBoxLayout;
    layoutEntradas->addWidget(labelZona);
    layoutEntradas->addWidget(labelCoste);
    layoutEntradas->addWidget(labelCantidad);
    layoutEntradas->addWidget(spinBoxEntradas);

    QDialogButtonBox *botonesEntradas = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layoutEntradas->addWidget(botonesEntradas);
    connect(botonesEntradas, &QDialogButtonBox::accepted, &dialogoEntradas, &QDialog::accept);
    connect(botonesEntradas, &QDialogButtonBox::rejected, &dialogoEntradas, &QDialog::reject);

    dialogoEntradas.setLayout(layoutEntradas);

    if (dialogoEntradas.exec() == QDialog::Accepted) {
        int cantidadEntradas = spinBoxEntradas->value();
        int precioTotal = precio * cantidadEntradas;

        QLabel *labelPrecioTotal = new QLabel("Precio Total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;
        QLabel *labelSector = new QLabel("Sector: Fondo Sur");
        layoutAsientos->addWidget(labelSector);

        QVector<int> asientosGenerados;
        for (int i = 0; i < cantidadEntradas; ++i) {
            int asiento = generarAsientos();

            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
            layoutAsientos->addWidget(labelAsiento);

            asientosGenerados.append(asiento);
        }

        layoutAsientos->addWidget(labelPrecioTotal);

        QHBoxLayout *layoutBotones = new QHBoxLayout;

        QPushButton *botonComprar = new QPushButton("Comprar");
        botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        botonComprar->setFixedSize(120,30);
        layoutBotones->addWidget(botonComprar);

        QPushButton *botonCancelar = new QPushButton("Cancelar Compra");
        botonCancelar->setStyleSheet("background-color:#ff6347; color:#fff; border-radius:10px;");
        botonCancelar->setFixedSize(120,30);
        layoutBotones->addWidget(botonCancelar);

        layoutAsientos->addLayout(layoutBotones);

        QDialog *nuevaVentana = new QDialog(this);
        nuevaVentana->setLayout(layoutAsientos);

        connect(botonComprar, &QPushButton::clicked, [=]() {
            for (int i = 0; i < cantidadEntradas; ++i) {
                QSqlQuery insertQuery;
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio) VALUES (:numAsiento, :precio)");
                insertQuery.bindValue(":numAsiento", asientosGenerados.at(i));
                insertQuery.bindValue(":precio", precio);

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            nuevaVentana->accept();
        });

        connect(botonCancelar, &QPushButton::clicked, nuevaVentana, &QDialog::reject);

        if (nuevaVentana->exec() == QDialog::Accepted) {
            qDebug() << "Compra realizada con éxito.";
        } else {
            qDebug() << "Se canceló la compra. No se guardará en la base de datos.";
        }
    } else {
        qDebug() << "No se seleccionaron entradas.";
    }
}


void asientos::on_pushButton_5_clicked()
{
    comprasCliente volver;
    volver.setWindowFlags(Qt::FramelessWindowHint);
    volver.setModal(true);
    hide();
    volver.exec();

}

