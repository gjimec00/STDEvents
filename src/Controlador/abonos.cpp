#include "abonos.h"
#include "ui_abonos.h"
#include "comprascliente.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QRandomGenerator>
#include <QtSql>

abonos::abonos(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::abonos)
{
    ui->setupUi(this);
}

abonos::~abonos()
{
    delete ui;
}

void abonos::setEvento(Evento evento){
    this->evento = evento;
}

Evento abonos::getEvento(){
    return evento;
}

void abonos::setCliente(Cliente cliente){
    this->cliente=cliente;
}

Cliente abonos::getCliente(){
    return cliente;
}

int abonos::generarAsientos(int min, int max) {
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
        numAsiento = QRandomGenerator::global()->bounded(min, max);
    } while (asientosOcupados.contains(numAsiento));

    return numAsiento;
}

void abonos::on_pushButton_4_clicked()
{
    int precio = 500;
    int min=1;
    int max=125;

    QDialog dialogoEntradas(this);

    QLabel *labelZona = new QLabel("Usted ha seleccionado Tribuna ");
    QLabel *labelCoste = new QLabel("El coste del abono en este sector es de 500€ ");

    QVBoxLayout *layoutEntradas = new QVBoxLayout;
    layoutEntradas->addWidget(labelZona);
    layoutEntradas->addWidget(labelCoste);

    QDialogButtonBox *botonesEntradas = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layoutEntradas->addWidget(botonesEntradas);
    connect(botonesEntradas, &QDialogButtonBox::accepted, &dialogoEntradas, &QDialog::accept);
    connect(botonesEntradas, &QDialogButtonBox::rejected, &dialogoEntradas, &QDialog::reject);

    dialogoEntradas.setLayout(layoutEntradas);

    if (dialogoEntradas.exec() == QDialog::Accepted) {
        int precioTotal = precio;

        QLabel *labelPrecioTotal = new QLabel("Precio Total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;
        QLabel *labelSector = new QLabel("Sector: Tribuna");
        layoutAsientos->addWidget(labelSector);

        QVector<int> asientosGenerados;
        int asiento = generarAsientos(min, max);
        QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
        layoutAsientos->addWidget(labelAsiento);
        asientosGenerados.append(asiento);
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

            QSqlQuery insertQuery;
            insertQuery.prepare("SELECT idEvento FROM eventos WHERE tipo = 'Deportivo'");
            insertQuery.exec();
            QVector<int> listaId;
            while (insertQuery.next()) {
                int id = insertQuery.value(0).toInt();
                listaId.push_back(id);
            }

            for(int i=0; i < listaId.size(); i++ ){
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento) VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asiento);
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", listaId[i]);

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }

            }


            insertQuery.prepare("UPDATE clientes  SET numAsientoAbonado =:numAsientoAbonado WHERE dni =:dni");
            insertQuery.bindValue(":numAsientoAbonado", asiento);
            insertQuery.bindValue(":dni", cliente.getDNI());
            if (insertQuery.exec()) {
                qDebug() << "Asiento y precio guardados en la base de datos.";
            } else {
                qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
            }

            QDateTime dateTimeActual = QDateTime::currentDateTime();
            QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
            QString horaActual = dateTimeActual.toString("hh:mm:ss");
            QSqlQuery insertQuery2;
            insertQuery2.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
            insertQuery2.bindValue(":fecha", fechaActual);
            insertQuery2.bindValue(":hora", horaActual);
            insertQuery2.bindValue(":dniCliente", cliente.getDNI());
            insertQuery2.bindValue(":precioTotal", precioTotal);

            if (insertQuery2.exec()) {
                qDebug() << "Pago insertado con éxito";
            } else {
                qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
            }

            QSqlQuery query;
            query.prepare("SELECT abonado FROM clientes WHERE dni = :dni");

            query.bindValue(":dni", cliente.getDNI());

            if (query.exec() && query.next()) {
                int abonado = 1;
                query.prepare("UPDATE clientes SET abonado= :abonado WHERE dni = :dni");
                query.bindValue(":dni", cliente.getDNI());
                query.bindValue(":abonado", abonado);
                query.exec();
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


void abonos::on_pushButton_3_clicked()
{
    int precio = 400;
    int min=126;
    int max=250;

    QDialog dialogoEntradas(this);

    QLabel *labelZona = new QLabel("Usted ha seleccionado Preferente ");
    QLabel *labelCoste = new QLabel("El coste del abono en este sector es de 400€ ");

    QVBoxLayout *layoutEntradas = new QVBoxLayout;
    layoutEntradas->addWidget(labelZona);
    layoutEntradas->addWidget(labelCoste);

    QDialogButtonBox *botonesEntradas = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layoutEntradas->addWidget(botonesEntradas);
    connect(botonesEntradas, &QDialogButtonBox::accepted, &dialogoEntradas, &QDialog::accept);
    connect(botonesEntradas, &QDialogButtonBox::rejected, &dialogoEntradas, &QDialog::reject);

    dialogoEntradas.setLayout(layoutEntradas);

    if (dialogoEntradas.exec() == QDialog::Accepted) {
        int precioTotal = precio;

        QLabel *labelPrecioTotal = new QLabel("Precio Total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;
        QLabel *labelSector = new QLabel("Sector: Preferente");
        layoutAsientos->addWidget(labelSector);

        QVector<int> asientosGenerados;
        int asiento = generarAsientos(min, max);
        QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
        layoutAsientos->addWidget(labelAsiento);
        asientosGenerados.append(asiento);
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

            QSqlQuery insertQuery;
            insertQuery.prepare("SELECT idEvento FROM eventos WHERE tipo = 'Deportivo'");
            insertQuery.exec();
            QVector<int> listaId;
            while (insertQuery.next()) {
                int id = insertQuery.value(0).toInt();
                listaId.push_back(id);
            }

            for(int i=0; i < listaId.size(); i++ ){
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento) VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asiento);
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", listaId[i]);

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }

            }


            insertQuery.prepare("UPDATE clientes  SET numAsientoAbonado =:numAsientoAbonado WHERE dni =:dni");
            insertQuery.bindValue(":numAsientoAbonado", asiento);
            insertQuery.bindValue(":dni", cliente.getDNI());
            if (insertQuery.exec()) {
                qDebug() << "Asiento y precio guardados en la base de datos.";
            } else {
                qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
            }

            QDateTime dateTimeActual = QDateTime::currentDateTime();
            QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
            QString horaActual = dateTimeActual.toString("hh:mm:ss");
            QSqlQuery insertQuery2;
            insertQuery2.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
            insertQuery2.bindValue(":fecha", fechaActual);
            insertQuery2.bindValue(":hora", horaActual);
            insertQuery2.bindValue(":dniCliente", cliente.getDNI());
            insertQuery2.bindValue(":precioTotal", precioTotal);

            if (insertQuery2.exec()) {
                qDebug() << "Pago insertado con éxito";
            } else {
                qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
            }

            QSqlQuery query;
            query.prepare("SELECT abonado FROM clientes WHERE dni = :dni");

            query.bindValue(":dni", cliente.getDNI());

            if (query.exec() && query.next()) {
                int abonado = 1;
                query.prepare("UPDATE clientes SET abonado= :abonado WHERE dni = :dni");
                query.bindValue(":dni", cliente.getDNI());
                query.bindValue(":abonado", abonado);
                query.exec();
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






void abonos::on_pushButton_2_clicked()
{
    int precio = 250;
    int min=251;
    int max=375;

    QDialog dialogoEntradas(this);

    QLabel *labelZona = new QLabel("Usted ha seleccionado Fondo Norte ");
    QLabel *labelCoste = new QLabel("El coste del abono en este sector es de 250€ ");

    QVBoxLayout *layoutEntradas = new QVBoxLayout;
    layoutEntradas->addWidget(labelZona);
    layoutEntradas->addWidget(labelCoste);

    QDialogButtonBox *botonesEntradas = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layoutEntradas->addWidget(botonesEntradas);
    connect(botonesEntradas, &QDialogButtonBox::accepted, &dialogoEntradas, &QDialog::accept);
    connect(botonesEntradas, &QDialogButtonBox::rejected, &dialogoEntradas, &QDialog::reject);

    dialogoEntradas.setLayout(layoutEntradas);

    if (dialogoEntradas.exec() == QDialog::Accepted) {
        int precioTotal = precio;

        QLabel *labelPrecioTotal = new QLabel("Precio Total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;
        QLabel *labelSector = new QLabel("Sector: Fondo Norte");
        layoutAsientos->addWidget(labelSector);

        QVector<int> asientosGenerados;
        int asiento = generarAsientos(min, max);
        QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
        layoutAsientos->addWidget(labelAsiento);
        asientosGenerados.append(asiento);
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

            QSqlQuery insertQuery;
            insertQuery.prepare("SELECT idEvento FROM eventos WHERE tipo = 'Deportivo'");
            insertQuery.exec();
            QVector<int> listaId;
            while (insertQuery.next()) {
                int id = insertQuery.value(0).toInt();
                listaId.push_back(id);
            }

            for(int i=0; i < listaId.size(); i++ ){
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento) VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asiento);
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", listaId[i]);

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }

            }


            insertQuery.prepare("UPDATE clientes  SET numAsientoAbonado =:numAsientoAbonado WHERE dni =:dni");
            insertQuery.bindValue(":numAsientoAbonado", asiento);
            insertQuery.bindValue(":dni", cliente.getDNI());
            if (insertQuery.exec()) {
                qDebug() << "Asiento y precio guardados en la base de datos.";
            } else {
                qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
            }

            QDateTime dateTimeActual = QDateTime::currentDateTime();
            QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
            QString horaActual = dateTimeActual.toString("hh:mm:ss");
            QSqlQuery insertQuery2;
            insertQuery2.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
            insertQuery2.bindValue(":fecha", fechaActual);
            insertQuery2.bindValue(":hora", horaActual);
            insertQuery2.bindValue(":dniCliente", cliente.getDNI());
            insertQuery2.bindValue(":precioTotal", precioTotal);

            if (insertQuery2.exec()) {
                qDebug() << "Pago insertado con éxito";
            } else {
                qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
            }

            QSqlQuery query;
            query.prepare("SELECT abonado FROM clientes WHERE dni = :dni");

            query.bindValue(":dni", cliente.getDNI());

            if (query.exec() && query.next()) {
                int abonado = 1;
                query.prepare("UPDATE clientes SET abonado= :abonado WHERE dni = :dni");
                query.bindValue(":dni", cliente.getDNI());
                query.bindValue(":abonado", abonado);
                query.exec();
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


void abonos::on_pushButton_clicked()
{
    int precio = 250;
    int min=376;
    int max=500;

    QDialog dialogoEntradas(this);

    QLabel *labelZona = new QLabel("Usted ha seleccionado Fondo Sur ");
    QLabel *labelCoste = new QLabel("El coste del abono en este sector es de 250€ ");

    QVBoxLayout *layoutEntradas = new QVBoxLayout;
    layoutEntradas->addWidget(labelZona);
    layoutEntradas->addWidget(labelCoste);

    QDialogButtonBox *botonesEntradas = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layoutEntradas->addWidget(botonesEntradas);
    connect(botonesEntradas, &QDialogButtonBox::accepted, &dialogoEntradas, &QDialog::accept);
    connect(botonesEntradas, &QDialogButtonBox::rejected, &dialogoEntradas, &QDialog::reject);

    dialogoEntradas.setLayout(layoutEntradas);

    if (dialogoEntradas.exec() == QDialog::Accepted) {
        int precioTotal = precio;

        QLabel *labelPrecioTotal = new QLabel("Precio Total: " + QString::number(precioTotal) + "€");
        QVBoxLayout *layoutAsientos = new QVBoxLayout;
        QLabel *labelSector = new QLabel("Sector: Fondo Sur");
        layoutAsientos->addWidget(labelSector);

        QVector<int> asientosGenerados;
        int asiento = generarAsientos(min, max);
        QLabel *labelAsiento = new QLabel("Su Número de asiento es el: " + QString::number(asiento));
        layoutAsientos->addWidget(labelAsiento);
        asientosGenerados.append(asiento);
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

            QSqlQuery insertQuery;
            insertQuery.prepare("SELECT idEvento FROM eventos WHERE tipo = 'Deportivo'");
            insertQuery.exec();
            QVector<int> listaId;
            while (insertQuery.next()) {
                int id = insertQuery.value(0).toInt();
                listaId.push_back(id);
            }

            for(int i=0; i < listaId.size(); i++ ){
                insertQuery.prepare("INSERT INTO asientos (numAsiento, precio, idEvento) VALUES (:numAsiento, :precio, :idEvento)");
                insertQuery.bindValue(":numAsiento", asiento);
                insertQuery.bindValue(":precio", precio);
                insertQuery.bindValue(":idEvento", listaId[i]);

                if (insertQuery.exec()) {
                    qDebug() << "Asiento y precio guardados en la base de datos.";
                } else {
                    qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
                }

            }


            insertQuery.prepare("UPDATE clientes  SET numAsientoAbonado =:numAsientoAbonado WHERE dni =:dni");
            insertQuery.bindValue(":numAsientoAbonado", asiento);
            insertQuery.bindValue(":dni", cliente.getDNI());
            if (insertQuery.exec()) {
                qDebug() << "Asiento y precio guardados en la base de datos.";
            } else {
                qDebug() << "Error al guardar en la base de datos:" << insertQuery.lastError().text();
            }

            QDateTime dateTimeActual = QDateTime::currentDateTime();
            QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
            QString horaActual = dateTimeActual.toString("hh:mm:ss");
            QSqlQuery insertQuery2;
            insertQuery2.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
            insertQuery2.bindValue(":fecha", fechaActual);
            insertQuery2.bindValue(":hora", horaActual);
            insertQuery2.bindValue(":dniCliente", cliente.getDNI());
            insertQuery2.bindValue(":precioTotal", precioTotal);

            if (insertQuery2.exec()) {
                qDebug() << "Pago insertado con éxito";
            } else {
                qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
            }

            QSqlQuery query;
            query.prepare("SELECT abonado FROM clientes WHERE dni = :dni");

            query.bindValue(":dni", cliente.getDNI());

            if (query.exec() && query.next()) {
                int abonado = 1;
                query.prepare("UPDATE clientes SET abonado= :abonado WHERE dni = :dni");
                query.bindValue(":dni", cliente.getDNI());
                query.bindValue(":abonado", abonado);
                query.exec();
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


void abonos::on_pushButton_5_clicked()
{
    comprasCliente volver;
    volver.setCliente(cliente);
    volver.setWindowFlags(Qt::FramelessWindowHint);
    volver.setModal(true);
    hide();
    volver.exec();

}

