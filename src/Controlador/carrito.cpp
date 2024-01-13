#include "carrito.h"
#include "ui_carrito.h"
#include "vistacliente.h"


carrito::carrito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::carrito)
{
    ui->setupUi(this);
    imprimirCarrito();
}

carrito::~carrito()
{
    delete ui;
}


void carrito::imprimirCarrito(){

}

