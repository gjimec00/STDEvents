#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <QDialog>

namespace Ui {
class administrador;
}

class administrador : public QDialog
{
    Q_OBJECT

public:
    explicit administrador(QWidget *parent = nullptr);
    ~administrador();

private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();

private:
    Ui::administrador *ui;
    bool ventanaCerrada;
};

#endif // ADMINISTRADOR_H
