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
    bool ventanaCerrada = true;
    bool ventanaCerradaP = true;
private slots:
    void on_menuBtn_clicked();

    void on_pushButton_8_clicked();

    void on_accountBtn_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::administrador *ui;
};

#endif // ADMINISTRADOR_H
