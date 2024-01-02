#ifndef COMPRAPRODUCTOS_H
#define COMPRAPRODUCTOS_H

#include <QDialog>

namespace Ui {
class compraProductos;
}

class compraProductos : public QDialog
{
    Q_OBJECT

public:
    explicit compraProductos(QWidget *parent = nullptr);
    ~compraProductos();

private:
    Ui::compraProductos *ui;
};

#endif // COMPRAPRODUCTOS_H
