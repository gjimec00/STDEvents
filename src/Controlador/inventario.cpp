#include "inventario.h"
#include "ui_inventario.h"
#include <QSqlQuery>
#include <QComboBox>
#include <QLabel>
#include "addproducto.h"
inventario::inventario(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::inventario)
{
    ui->setupUi(this);
    mostrarInventario();
}

inventario::~inventario()
{
    delete ui;
}

void inventario::mostrarInventario(){


    QVBoxLayout *menuDesp = new QVBoxLayout();

    QSqlQuery queryProductos;
    queryProductos.prepare("SELECT nombre, cantidad, precio, descripcion, talla, color FROM productos");

    if (!queryProductos.exec()) {
        return;
    }


    while (queryProductos.next()) {
        QWidget *wid = new QWidget();
        QHBoxLayout *hor = new QHBoxLayout();
        QFrame *frame = new QFrame();
        QVBoxLayout *menuDesp2 = new QVBoxLayout();

        QLabel *label1 = new QLabel("Nombre: " + queryProductos.value("nombre").toString());
        QLabel *label2 = new QLabel("Precio: " + queryProductos.value("precio").toString());
        QLabel *label3 = new QLabel("Descripcion: " + queryProductos.value("descripcion").toString());
        QLabel *label4 = new QLabel("Talla: " + queryProductos.value("talla").toString());
        QLabel *label5 = new QLabel("Color: " + queryProductos.value("color").toString());
        QLabel *label6 = new QLabel("Cantidad: " + queryProductos.value("cantidad").toString());

        menuDesp2->addWidget(label1);
        menuDesp2->addWidget(label2);
        menuDesp2->addWidget(label3);
        menuDesp2->addWidget(label4);
        menuDesp2->addWidget(label5);
        menuDesp2->addWidget(label6);
        frame->setLayout(menuDesp2);
        hor->addWidget(frame);
        wid->setStyleSheet("border:1px solid grey;");
        wid->setLayout(hor);
        menuDesp->addWidget(wid);

    }
    ui->scrollAreaWidgetContents->setLayout(menuDesp);
}

void inventario::on_pushButton_clicked()
{
    addproducto addproducto;
    addproducto.setWindowFlags(Qt::FramelessWindowHint);
    addproducto.setModal(true);
    hide();
    addproducto.exec();
}

