#include "entradasyabonos.h"
#include "ui_entradasyabonos.h"

entradasyabonos::entradasyabonos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::entradasyabonos)
{
    ui->setupUi(this);
    ui->quickWidget->setSource(QUrl("qrc:Files/qml/entradasyabonos.qml"));
}

entradasyabonos::~entradasyabonos()
{
    delete ui;
}
