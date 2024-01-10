#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>
#include "src/Modelo/database.h"

namespace Ui {
class registro;
}

class registro : public QDialog
{
    Q_OBJECT

public:
    explicit registro(QWidget *parent = nullptr);
    ~registro();
    void verificarContraseñas();
    void verificarDni();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::registro *ui;
};

#endif // REGISTRO_H
