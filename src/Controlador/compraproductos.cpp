#include "compraproductos.h"
#include "ui_compraproductos.h"

compraProductos::compraProductos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::compraProductos)
{
    ui->setupUi(this);
}

compraProductos::~compraProductos()
{
    delete ui;
}
