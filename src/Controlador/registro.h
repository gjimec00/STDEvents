#ifndef REGISTRO_H
#define REGISTRO_H

#include <QDialog>

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

private slots:
    void on_pushButton_clicked();

private:
    Ui::registro *ui;

};

#endif // REGISTRO_H
