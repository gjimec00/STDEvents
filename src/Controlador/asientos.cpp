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

void asientos::setCliente(Cliente cliente){
    this->cliente=cliente;
}

Cliente asientos::getCliente(){
    return cliente;
}

/*
QVector<int> asientos::generarAsientos(int min, int max, int cantidadEntradas) {
    QSqlQuery asientosQuery;
    QVector<int> asientosOcupados;
    QVector<int> asientosGenerados;
    int numAsiento;


    asientosQuery.prepare("SELECT numAsiento FROM asientos");
    if (asientosQuery.exec()) {
        while (asientosQuery.next()) {
            asientosOcupados.append(asientosQuery.value("numAsiento").toInt());
        }
    }

    while (asientosGenerados.size() < cantidadEntradas){
        numAsiento = QRandomGenerator::global()->bounded(min, max);

        if(!asientosGenerados.contains(numAsiento) && !asientosOcupados.contains(numAsiento)){
            asientosGenerados.append(numAsiento);
        }
    }
    return asientosGenerados;

}*/

QVector<int> asientos::generarAsientos(int min, int max, int cantidadEntradas) {
    QSqlQuery asientosQuery;
    QVector<int> asientosOcupados;
    QVector<int> asientosDisponibles;
    QVector<int> asientosGenerados;

    asientosQuery.prepare("SELECT numAsiento FROM asientos");
    if (asientosQuery.exec()) {
        while (asientosQuery.next()) {
            asientosOcupados.append(asientosQuery.value("numAsiento").toInt());
        }
    }

    // Crear lista de asientos disponibles
    for (int asiento = min; asiento <= max; ++asiento) {
        if (!asientosOcupados.contains(asiento)) {
            asientosDisponibles.append(asiento);
        }
    }

    if (cantidadEntradas > 1) {
        // Si se compran más de una entrada, generamos asientos ordenados
        if (asientosDisponibles.size() >= cantidadEntradas) {
            for (int i = 0; i < cantidadEntradas; ++i) {
                asientosGenerados.append(asientosDisponibles[i]);
            }
        } else {
            // Manejar el caso en que no hay suficientes asientos disponibles
            // Puedes emitir una señal o manejar la situación de alguna otra manera
            qDebug() << "No hay suficientes asientos disponibles.";
        }
    } else {
        // Si es solo una entrada, generamos un asiento aleatorio
        if (!asientosDisponibles.isEmpty()) {
            int numAsiento = QRandomGenerator::global()->bounded(asientosDisponibles.size());
            asientosGenerados.append(asientosDisponibles[numAsiento]);
        } else {
            // Manejar el caso en que no hay asientos disponibles
            // Puedes emitir una señal o manejar la situación de alguna otra manera
            qDebug() << "No hay asientos disponibles.";
        }
    }

    return asientosGenerados;
}




void asientos::on_pushButton_4_clicked()
{
    int j = 0;
    int precio = 50;
    int max = 125;
    int min = 1;

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
        //QVector<int> asientosAnteriores;

        QVector<int> asientos = generarAsientos(min,max, cantidadEntradas);
        for (int i = 0; i < cantidadEntradas; ++i) {

            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asientos[i]));
            layoutAsientos->addWidget(labelAsiento);

            asientosGenerados.append(asientos[i]);
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
                insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            QDateTime dateTimeActual = QDateTime::currentDateTime();
            QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
            QString horaActual = dateTimeActual.toString("hh:mm:ss");
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
            //insertQuery.bindValue(":idPago", idPago);
            insertQuery.bindValue(":fecha", fechaActual);
            insertQuery.bindValue(":hora", horaActual);
            insertQuery.bindValue(":dniCliente", cliente.getDNI());
            insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());
            //insertQuery.bindValue(":idProducto", cliente.listaProductos[i]->getIdProducto());
            insertQuery.bindValue(":precioTotal", precioTotal);

            if (insertQuery.exec()) {
                qDebug() << "Pago insertado con éxito";
            } else {
                qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
            }

            nuevaVentana->accept();

        });
        j++;

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

/*
void asientos::on_pushButton_4_clicked()
{
    int j = 0;
    int precio = 50;
    int max = 125;
    int min = 1;

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

        QVector<int> asientosGenerados = generarAsientosOrdenados(min, max, cantidadEntradas);

        for (int i = 0; i < cantidadEntradas; ++i) {
            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asientosGenerados[i]));
            layoutAsientos->addWidget(labelAsiento);
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
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento) VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asientosGenerados[i]);
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            // Resto del código para insertar el pago en la base de datos
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
}*/


void asientos::on_pushButton_3_clicked()
{
    int j = 0;
    int precio = 40;
    int min = 126;
    int max = 250;

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
        QVector<int> asientos = generarAsientos(min,max, cantidadEntradas);
        for (int i = 0; i < cantidadEntradas; ++i) {

            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asientos[i]));
            layoutAsientos->addWidget(labelAsiento);

            asientosGenerados.append(asientos[i]);
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
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento) VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asientosGenerados.at(i));
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            QDateTime dateTimeActual = QDateTime::currentDateTime();
            QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
            QString horaActual = dateTimeActual.toString("hh:mm:ss");
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
            //insertQuery.bindValue(":idPago", idPago);
            insertQuery.bindValue(":fecha", fechaActual);
            insertQuery.bindValue(":hora", horaActual);
            insertQuery.bindValue(":dniCliente", cliente.getDNI());
            insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());
            //insertQuery.bindValue(":idProducto", cliente.listaProductos[i]->getIdProducto());
            insertQuery.bindValue(":precioTotal", precioTotal);

            if (insertQuery.exec()) {
                qDebug() << "Pago insertado con éxito";
            } else {
                qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
            }

            nuevaVentana->accept();
        });
        j++;
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
    int j = 0;
    int precio = 25;
    int min = 251;
    int max = 375;

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
        QVector<int> asientos = generarAsientos(min,max, cantidadEntradas);
        for (int i = 0; i < cantidadEntradas; ++i) {

            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asientos[i]));
            layoutAsientos->addWidget(labelAsiento);

            asientosGenerados.append(asientos[i]);
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
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento) VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asientosGenerados.at(i));
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            QDateTime dateTimeActual = QDateTime::currentDateTime();
            QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
            QString horaActual = dateTimeActual.toString("hh:mm:ss");
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
            //insertQuery.bindValue(":idPago", idPago);
            insertQuery.bindValue(":fecha", fechaActual);
            insertQuery.bindValue(":hora", horaActual);
            insertQuery.bindValue(":dniCliente", cliente.getDNI());
            insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());
            //insertQuery.bindValue(":idProducto", cliente.listaProductos[i]->getIdProducto());
            insertQuery.bindValue(":precioTotal", precioTotal);

            if (insertQuery.exec()) {
                qDebug() << "Pago insertado con éxito";
            } else {
                qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
            }

            nuevaVentana->accept();
        });
        j++;

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
    int j = 0;
    int precio = 25;
    int min = 376;
    int max = 500;

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
        QVector<int> asientos = generarAsientos(min,max, cantidadEntradas);
        for (int i = 0; i < cantidadEntradas; ++i) {

            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asientos[i]));
            layoutAsientos->addWidget(labelAsiento);

            asientosGenerados.append(asientos[i]);
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
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento) VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asientosGenerados.at(i));
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }
            }
            QDateTime dateTimeActual = QDateTime::currentDateTime();
            QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
            QString horaActual = dateTimeActual.toString("hh:mm:ss");
            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
            //insertQuery.bindValue(":idPago", idPago);
            insertQuery.bindValue(":fecha", fechaActual);
            insertQuery.bindValue(":hora", horaActual);
            insertQuery.bindValue(":dniCliente", cliente.getDNI());
            insertQuery.bindValue(":idEvento", cliente.listaEventos[j]->getIdEvento());
            //insertQuery.bindValue(":idProducto", cliente.listaProductos[i]->getIdProducto());
            insertQuery.bindValue(":precioTotal", precioTotal);

            if (insertQuery.exec()) {
                qDebug() << "Pago insertado con éxito";
            } else {
                qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
            }

            nuevaVentana->accept();
        });
        j++;

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


