#include "entradasyabonos.h"
#include "ui_entradasyabonos.h"

entradasyabonos::entradasyabonos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::entradasyabonos)
{
    ui->setupUi(this);
}

entradasyabonos::~entradasyabonos()
{
    delete ui;
}
