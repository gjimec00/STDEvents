#ifndef COMPRASCLIENTE_H
#define COMPRASCLIENTE_H

#include <QDialog>

namespace Ui {
class comprasCliente;
}

class comprasCliente : public QDialog
{
    Q_OBJECT

public:
    explicit comprasCliente(QWidget *parent = nullptr);
    ~comprasCliente();

private:
    Ui::comprasCliente *ui;
};

#endif // COMPRASCLIENTE_H
