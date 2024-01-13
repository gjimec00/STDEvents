#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <QDialog>

namespace Ui {
class inventario;
}

class inventario : public QDialog
{
    Q_OBJECT

public:
    explicit inventario(QWidget *parent = nullptr);
    ~inventario();
    void mostrarInventario();

private slots:
    void on_pushButton_clicked();

private:
    Ui::inventario *ui;
};

#endif // INVENTARIO_H
