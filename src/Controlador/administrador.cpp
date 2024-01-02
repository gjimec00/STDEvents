#include "administrador.h"
#include "ui_administrador.h"

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
