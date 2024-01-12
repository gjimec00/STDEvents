#include "entradasyabonos.h"
#include "ui_entradasyabonos.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

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

void entradasyabonos::mostrarVista(){
    QVBoxLayout *menuDesp = new QVBoxLayout();
    for (int i = 0; i < 15; i++){
        QWidget * wid = new QWidget();
        QHBoxLayout * hor = new QHBoxLayout();
        QFrame * frame = new QFrame();
        QVBoxLayout *menuDesp2 = new QVBoxLayout();
        QLabel * label1 = new QLabel("Prueba1");
        QLabel * label2 = new QLabel("Prueba2");
        QLabel * label3 = new QLabel("Prueba3");
        QLabel * label4 = new QLabel("Prueba4");
        QLabel * label5 = new QLabel("Prueba5");
        QPushButton * button = new QPushButton("Comprar");
        wid->setLayout(hor);
        frame->setLayout(menuDesp2);
        menuDesp2->addWidget(label1);
        menuDesp2->addWidget(label2);
        menuDesp2->addWidget(label3);
        menuDesp2->addWidget(label4);
        menuDesp2->addWidget(label5);
        hor->addWidget(frame);
        hor->addWidget(button);
        menuDesp->addWidget(wid);
    }
    ui->scrollAreaWidgetContents->setLayout(menuDesp);
}
