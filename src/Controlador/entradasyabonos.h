#ifndef ENTRADASYABONOS_H
#define ENTRADASYABONOS_H

#include <QDialog>

namespace Ui {
class entradasyabonos;
}

class entradasyabonos : public QDialog
{
    Q_OBJECT

public:
    explicit entradasyabonos(QWidget *parent = nullptr);
    ~entradasyabonos();
    void mostrarVista();

private:
    Ui::entradasyabonos *ui;
};

#endif // ENTRADASYABONOS_H
