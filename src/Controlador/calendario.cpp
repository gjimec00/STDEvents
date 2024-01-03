#include "calendario.h"
#include "ui_calendario.h"
#include <QApplication>
#include <QPushButton>
#include <QMenu>
#include <QAction>

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
