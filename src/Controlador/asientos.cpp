// asientos.cpp
#include "asientos.h"
#include "ui_asientos.h"
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

int asientos::generarAsientos() {
    QSqlQuery asientosQuery;
    QVector<int> asientosOcupados;

    asientosQuery.prepare("SELECT numAsiento FROM asientos");
    if (asientosQuery.exec()) {
        while (asientosQuery.next()) {
            asientosOcupados.append(asientosQuery.value("numAsiento").toInt());
        }
    }

    int numAsiento;
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
    spinBoxEntradas->setRange(1, 10);
    labelCantidad->setBuddy(spinBoxEntradas);

    int asiento;
    QVBoxLayout *layoutEntradas = new QVBoxLayout;
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

        QLabel *labelPrecioTotal = new QLabel("Precio total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;

        QLabel *labelZona = new QLabel("Usted ha seleccionado Tribuna ");
        layoutAsientos->addWidget(labelZona);
        for (int i = 0; i < cantidadEntradas; ++i) {
            asiento = generarAsientos();
            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
            layoutAsientos->addWidget(labelAsiento);

            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO asientos (numAsiento, precio) VALUES (:numAsiento, :precio)");
            insertQuery.bindValue(":numAsiento", asiento);
            insertQuery.bindValue(":precio", precio);

            if (insertQuery.exec()) {
                qDebug() << "Asiento y precio guardados en la base de datos.";
            } else {
                qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
            }
        }

        layoutAsientos->addWidget(labelPrecioTotal);

        QPushButton *botonComprar = new QPushButton("Comprar");
        botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        botonComprar->setFixedSize(85,30);
        layoutAsientos->addWidget(botonComprar);

        QDialog *nuevaVentana = new QDialog(this);
        nuevaVentana->setLayout(layoutAsientos);
        connect(botonComprar, &QPushButton::clicked, nuevaVentana, &QDialog::accept);

        if (nuevaVentana->exec() == QDialog::Accepted) {
        } else {
            qDebug() << "La ventana se cerró sin aceptar. No se guardará en la base de datos.";
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
    spinBoxEntradas->setRange(1, 10);
    labelCantidad->setBuddy(spinBoxEntradas);

    int asiento;
    QVBoxLayout *layoutEntradas = new QVBoxLayout;
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

        QLabel *labelPrecioTotal = new QLabel("Precio total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;

        QLabel *labelZona = new QLabel("Usted ha seleccionado Preferente ");
        layoutAsientos->addWidget(labelZona);
        for (int i = 0; i < cantidadEntradas; ++i) {
            asiento = generarAsientos();
            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
            layoutAsientos->addWidget(labelAsiento);

            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO asientos (numAsiento, precio) VALUES (:numAsiento, :precio)");
            insertQuery.bindValue(":numAsiento", asiento);
            insertQuery.bindValue(":precio", precio);

            if (insertQuery.exec()) {
                qDebug() << "Asiento y precio guardados en la base de datos.";
            } else {
                qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
            }
        }

        layoutAsientos->addWidget(labelPrecioTotal);

        QPushButton *botonComprar = new QPushButton("Comprar");
        botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        botonComprar->setFixedSize(85,30);
        layoutAsientos->addWidget(botonComprar);

        QDialog *nuevaVentana = new QDialog(this);
        nuevaVentana->setLayout(layoutAsientos);
        connect(botonComprar, &QPushButton::clicked, nuevaVentana, &QDialog::accept);

        if (nuevaVentana->exec() == QDialog::Accepted) {
        } else {
            qDebug() << "La ventana se cerró sin aceptar. No se guardará en la base de datos.";
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
    spinBoxEntradas->setRange(1, 10);
    labelCantidad->setBuddy(spinBoxEntradas);

    int asiento;
    QVBoxLayout *layoutEntradas = new QVBoxLayout;
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

        QLabel *labelPrecioTotal = new QLabel("Precio total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;

        QLabel *labelZona = new QLabel("Usted ha seleccionado Fondo Norte ");
        layoutAsientos->addWidget(labelZona);
        for (int i = 0; i < cantidadEntradas; ++i) {
            asiento = generarAsientos();
            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
            layoutAsientos->addWidget(labelAsiento);

            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO asientos (numAsiento, precio) VALUES (:numAsiento, :precio)");
            insertQuery.bindValue(":numAsiento", asiento);
            insertQuery.bindValue(":precio", precio);

            if (insertQuery.exec()) {
                qDebug() << "Asiento y precio guardados en la base de datos.";
            } else {
                qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
            }
        }

        layoutAsientos->addWidget(labelPrecioTotal);

        QPushButton *botonComprar = new QPushButton("Comprar");
        botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        botonComprar->setFixedSize(85,30);
        layoutAsientos->addWidget(botonComprar);

        QDialog *nuevaVentana = new QDialog(this);
        nuevaVentana->setLayout(layoutAsientos);
        connect(botonComprar, &QPushButton::clicked, nuevaVentana, &QDialog::accept);

        if (nuevaVentana->exec() == QDialog::Accepted) {
        } else {
            qDebug() << "La ventana se cerró sin aceptar. No se guardará en la base de datos.";
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
    spinBoxEntradas->setRange(1, 10);
    labelCantidad->setBuddy(spinBoxEntradas);

    int asiento;
    QVBoxLayout *layoutEntradas = new QVBoxLayout;
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

        QLabel *labelPrecioTotal = new QLabel("Precio total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;

        QLabel *labelZona = new QLabel("Usted ha seleccionado Fondo Sur ");
        layoutAsientos->addWidget(labelZona);
        for (int i = 0; i < cantidadEntradas; ++i) {
            asiento = generarAsientos();
            QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
            layoutAsientos->addWidget(labelAsiento);

            QSqlQuery insertQuery;
            insertQuery.prepare("INSERT INTO asientos (numAsiento, precio) VALUES (:numAsiento, :precio)");
            insertQuery.bindValue(":numAsiento", asiento);
            insertQuery.bindValue(":precio", precio);

            if (insertQuery.exec()) {
                qDebug() << "Asiento y precio guardados en la base de datos.";
            } else {
                qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
            }
        }

        layoutAsientos->addWidget(labelPrecioTotal);

        QPushButton *botonComprar = new QPushButton("Comprar");
        botonComprar->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        botonComprar->setFixedSize(85,30);
        layoutAsientos->addWidget(botonComprar);

        QDialog *nuevaVentana = new QDialog(this);
        nuevaVentana->setLayout(layoutAsientos);
        connect(botonComprar, &QPushButton::clicked, nuevaVentana, &QDialog::accept);

        if (nuevaVentana->exec() == QDialog::Accepted) {
        } else {
            qDebug() << "La ventana se cerró sin aceptar. No se guardará en la base de datos.";
        }
    } else {
        qDebug() << "No se seleccionaron entradas.";
    }
}

