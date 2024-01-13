#include "comprascliente.h"
#include "ui_comprascliente.h"

comprasCliente::comprasCliente(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::comprasCliente)
{
    ui->setupUi(this);
}

comprasCliente::~comprasCliente()
{
    delete ui;
}
