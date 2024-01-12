#include "calendario.h"
#include "ui_calendario.h"
#include <QApplication>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>

Calendario::Calendario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calendario)
{
    ui->setupUi(this);

}

Calendario::~Calendario()
{
    delete ui;
}

void Calendario::on_calendarWidget_activated(const QDate &date)
{
    QSqlQuery query;
    query.prepare("SELECT nombre, fecha, hora, descripcion, tipo FROM eventos WHERE fecha = :fecha");
    query.bindValue(":fecha", date);

    if (!query.exec()) {
        qDebug() << "Error al ejecutar la consulta:" << query.lastError().text();
        return;
    }
    QStringList resultados;
    // Procesar los resultados
    while (query.next()) {
        QString col1 = query.value(0).toString();
        QString col2 = query.value(1).toString();
        QString col3 = query.value(2).toString();
        QString col4 = query.value(3).toString();
        QString col5 = query.value(4).toString();
        QString resultado = "Nombre del evento: " + col1 + ", fecha: " + col2 + ", hora: " + col3 + ", descripcion: " + col4 + ", tipo: " + col5;
        resultados.append(resultado);
    }
    if (!resultados.isEmpty())    {
        QString resultadosStr = resultados.join("\n");
        ui->label_2->setText(resultadosStr);
    }else{
        ui->label_2->setText("No hay eventos programados disponibles para este día");
    }
}


void Calendario::on_pushButton_clicked()
{
    close();
}

