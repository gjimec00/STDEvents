#include "carrito.h"
#include "qpropertyanimation.h"
#include "ui_carrito.h"
#include "src/Modelo/dao/cliente.h"
#include "src/Modelo/dao/producto.h"
#include "src/Modelo/dao/evento.h"
#include "vistacliente.h"
#include "comprascliente.h"
#include <QtSql>
#include <QDateTime>

bool ventanaCerrada3C = true;
bool ventanaCerrada3CP = true;
carrito::carrito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::carrito)
{
    ui->setupUi(this);

}

carrito::~carrito()
{
    delete ui;
}

void carrito::setCliente(Cliente cliente){
    this->cliente=cliente;
}

Cliente carrito::getCliente(){
    return cliente;
}

void carrito::setProducto(Producto producto){
    this->producto=producto;
}

Producto carrito::getProducto(){
    return producto;
}

void carrito::setEvento(Evento evento){
    this->evento=evento;
}

Evento carrito::getEvento(){
    return evento;
}


void carrito::on_menuBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->leftMenu, "pos");
    animation->setDuration(500);
    QPropertyAnimation *animationDespl = new QPropertyAnimation(this, "geometry");
    animationDespl->setDuration(500);
    QPropertyAnimation *animationMenu = new QPropertyAnimation(ui->mainBody, "pos");
    animationMenu->setDuration(500);
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->profileCont, "pos");
    animation2->setDuration(500);

    QRect geometry = this->geometry();
    if (ventanaCerrada3C){
        geometry.setWidth(1150);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(-220, 0));
        animation->setEndValue(QPoint(0, 0));

        animationMenu->setStartValue(QPoint(0, 0));
        animationMenu->setEndValue(QPoint(220, 0));

        animation2->setStartValue(QPoint(1030, 0));
        animation2->setEndValue(QPoint(1150, 0));
        ventanaCerrada3C = false;


    } else{
        geometry.setWidth(930);
        geometry.setHeight(548);
        animationDespl->setEndValue(geometry);

        animation->setStartValue(QPoint(0, 0));
        animation->setEndValue(QPoint(-220, 0));

        animationMenu->setStartValue(QPoint(220, 0));
        animationMenu->setEndValue(QPoint(0, 0));

        animation2->setStartValue(QPoint(1250, 0));
        animation2->setEndValue(QPoint(930, 0));
        ventanaCerrada3C = true;
    }
    animationDespl->start();

    animation->start();

    animationMenu->start();

    animation2->start();


}


void carrito::on_pushButton_8_clicked()
{
    close();
}


void carrito::on_accountBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    QRect geometry = this->geometry();
    if (ventanaCerrada3C){
        if(ventanaCerrada3CP){
            geometry.setWidth(1030);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada3CP = false;
        }else{
            geometry.setWidth(930);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada3CP = true;
        }
    } else{
        if(ventanaCerrada3CP){
            geometry.setWidth(1250);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada3CP = false;
        }else{
            geometry.setWidth(1150);
            geometry.setHeight(548);
            animation->setEndValue(geometry);
            ventanaCerrada3CP = true;
        }
    }
    animation->start();

}

void carrito::imprimirCarrito(){
    qDebug() << "Imprimiendo el contenido del carrito...";
    QVBoxLayout *menuDesp = new QVBoxLayout();

    for(size_t i = 0; i < cliente.listaProductos.size(); i++){

        QWidget *wid = new QWidget();
        QHBoxLayout *hor = new QHBoxLayout();
        QFrame *frame = new QFrame();
        QVBoxLayout *menuDesp2 = new QVBoxLayout();

        Producto *producto = cliente.listaProductos[i];
        double precio1 = producto->getPrecio();
        QString valorQString = QString::number(precio1);
        QLabel *label1 = new QLabel(producto->getDescrpicion());

        QLabel *label2 = new QLabel("Precio total: " + QString::number(precio1 * producto->getCantidad()) + "€");
        QLabel *label3 = new QLabel("Cantidad: " + QString::number(producto->getCantidad()));
        QLabel *label4 = new QLabel(producto->getTalla());
        QLabel *label5 = new QLabel(producto->getColor());

        menuDesp2->addWidget(label1);
        menuDesp2->addWidget(label2);
        menuDesp2->addWidget(label3);
        menuDesp2->addWidget(label4);
        menuDesp2->addWidget(label5);
        frame->setLayout(menuDesp2);
        hor->addWidget(frame);
        wid->setStyleSheet("border:1px solid grey;");
        wid->setLayout(hor);
        menuDesp->addWidget(wid);

    }
    ui->scrollAreaWidgetContents_4->setLayout(menuDesp);
}




void carrito::on_pushButton_4_clicked()
{
    vistaCliente vistaC;
    vistaC.setCliente(cliente);
    vistaC.setWindowFlags(Qt::FramelessWindowHint);
    vistaC.setModal(true);
    hide();
    ventanaCerrada3C = true;
    ventanaCerrada3CP = true;
    vistaC.exec();
}


void carrito::on_pushButton_6_clicked()
{
    comprasCliente comprasC;
    comprasC.setCliente(cliente);
    comprasC.setWindowFlags(Qt::FramelessWindowHint);
    comprasC.setModal(true);
    hide();
    ventanaCerrada3C = true;
    ventanaCerrada3CP = true;
    comprasC.exec();
}


void carrito::on_pushButton_2_clicked()
{

    QDateTime dateTimeActual = QDateTime::currentDateTime();
    QString fechaActual = dateTimeActual.toString("yyyy-MM-dd");  // Formato de fecha: Año-Mes-Día
    QString horaActual = dateTimeActual.toString("hh:mm:ss");     // Formato de hora: Hora:Minuto:Segundo

    for(size_t i = 0; i < cliente.listaProductos.size(); i++){
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO pagos (fecha, hora, dniCliente, idEvento, idProducto, precioTotal) VALUES (:fecha, :hora, :dniCliente, :idEvento, :idProducto, :precioTotal)");
        insertQuery.bindValue(":fecha", fechaActual);
        insertQuery.bindValue(":hora", horaActual);
        insertQuery.bindValue(":dniCliente", cliente.getDNI());
        insertQuery.bindValue(":idProducto", cliente.listaProductos[i]->getIdProducto());
        insertQuery.bindValue(":precioTotal", cliente.listaProductos[i]->getPrecio() * cliente.listaProductos[i]->getCantidad());

        if (insertQuery.exec()) {
            qDebug() << "Pago insertado con éxito";
        } else {
            qDebug() << "Error al insertar pago." << insertQuery.lastError().text();
        }
    }


    for(size_t i = 0; i < cliente.listaProductos.size(); i++){
        QSqlQuery query;
        query.prepare("SELECT cantidad FROM productos WHERE idProducto = :idProducto");

        query.bindValue(":idProducto", cliente.listaProductos[i]->getIdProducto());


        if (query.exec() && query.next()) {
            int cantidad = query.value(0).toInt();
            cantidad -=  cliente.listaProductos[i]->getCantidad();
            query.prepare("UPDATE productos SET cantidad= :cantidad WHERE idProducto = :idProducto");
            query.bindValue(":idProducto", cliente.listaProductos[i]->getIdProducto());
            query.bindValue(":cantidad", cantidad);
            query.exec();
        }
    }

    cliente.listaProductos.clear();

    QLayout *layout = ui->scrollAreaWidgetContents_4->layout();

    // Verificar si hay un layout asignado
    if (layout) {
        // Eliminar y liberar los widgets contenidos en el layout
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Asignar un nuevo layout vacío al scrollAreaWidgetContents_4
        ui->scrollAreaWidgetContents_4->setLayout(new QVBoxLayout());
    }


    QDialog dialogoPago(this);
    QLabel *labelPago = new QLabel(" Se han pagado los productos del carrito.");
    QVBoxLayout *layoutPago = new QVBoxLayout;
    layoutPago->addWidget(labelPago);
    dialogoPago.setLayout(layoutPago);
    dialogoPago.exec();
}


void carrito::on_pushButton_clicked()
{
    cliente.listaProductos.clear();

    QLayout *layout = ui->scrollAreaWidgetContents_4->layout();

    // Verificar si hay un layout asignado
    if (layout) {
        // Eliminar y liberar los widgets contenidos en el layout
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }

        // Asignar un nuevo layout vacío al scrollAreaWidgetContents_4
        ui->scrollAreaWidgetContents_4->setLayout(new QVBoxLayout());
    }

    QDialog dialogoVaciar(this);
    QLabel *labelVaciar = new QLabel(" Se han borrado los productos del carrito.");
    QVBoxLayout *layoutVaciar = new QVBoxLayout;
    layoutVaciar->addWidget(labelVaciar);
    dialogoVaciar.setLayout(layoutVaciar);
    dialogoVaciar.exec();
}

