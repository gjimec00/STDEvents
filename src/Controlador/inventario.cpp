#include "inventario.h"
#include "ui_inventario.h"
#include <QSqlQuery>
#include <QComboBox>
#include <QLabel>

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
    int numeroDeFilas = 0;
    int cantidad=0;
    QSqlQuery queryCount;
    queryCount.prepare("SELECT COUNT(*) FROM eventos");

    if (!queryCount.exec()) {
        return;
    }

    if (queryCount.next()) {
        numeroDeFilas = queryCount.value(0).toInt();
    }

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
        //QComboBox *combo = new QComboBox();

        cantidad=queryProductos.value(1).toInt();
        for(int i=1; i<=cantidad; i++){
            //combo->addItem(QString::number(i));
        }

        QLabel *label1 = new QLabel("Nombre: " + queryProductos.value("nombre").toString());
        QLabel *label2 = new QLabel("Precio: " + queryProductos.value("precio").toString());
        QLabel *label3 = new QLabel("Descripcion: " + queryProductos.value("descripcion").toString());
        QLabel *label4 = new QLabel("Talla: " + queryProductos.value("talla").toString());
        QLabel *label5 = new QLabel("Color: " + queryProductos.value("color").toString());
        QLabel *label6 = new QLabel("Cantidad: " + queryProductos.value("cantidad").toString());

        //QPushButton *button = new QPushButton("Comprar");

        menuDesp2->addWidget(label1);
        menuDesp2->addWidget(label2);
        menuDesp2->addWidget(label3);
        menuDesp2->addWidget(label4);
        menuDesp2->addWidget(label5);
        menuDesp2->addWidget(label6);
        //button->setStyleSheet("background-color:#01ff78; color:#fff; border-radius:10px;");
        //button->setFixedSize(85,30);
        frame->setLayout(menuDesp2);
        hor->addWidget(frame);
        //combo->setFixedSize(65,15);
        //hor->addWidget(combo);
        //hor->addWidget(button);
        wid->setStyleSheet("border:1px solid grey;");
        wid->setLayout(hor);
        menuDesp->addWidget(wid);

    }
    ui->scrollAreaWidgetContents->setLayout(menuDesp);
}

void inventario::on_pushButton_clicked()
{
    close();
}

